/*
 * Level.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#include "Level.h"
#include "MsgBox.h"

#include <iostream>
#include <set>

namespace netrom {
Level::Level(Netrom * gameEngine, std::string name) {
	this->world = new GlyphMat();
	this->worldMask = new GlyphMat();
	this->nextGOId = 0;
	this->gameEngine = gameEngine;
	this->levelPath = this->gameEngine->getRes() / "levels" / name
			/ (name + ".lua");
	this->script = new LuaScript(this, this->levelPath);
	this->script->load();
}

Level::~Level() {
	delete this->script;
	delete this->world;
	delete this->worldMask;

	for (auto go: this->gameObjects) {
		delete go;
	}

	for (auto ue: this->uiElements) {
		delete ue;
	}
}

GlyphMat * Level::mergeWorld(std::list<Drawable *> dl) {
	GlyphMat * dr;
	int mx = 0, my = 0, mmx = 0, mmy = 0;
	std::list<std::tuple<GlyphMat*, GlyphMat*, int, int>> sd;

	for (auto d : dl) {
		GlyphMat * dd = d->draw();
		int ux, uy;
		int uw, uh;
		std::tie(uw, uh) = dd->getSize();
		std::tie(ux, uy) = d->getPos();
		sd.push_back(std::make_tuple(dd, d->getMask(), ux, uy));

		if (mx < ux + uw)
			mx = ux + uw;

		if (my < uy + uh)
			my = uy + uh;

		if (mmx > ux)
			mmx = ux;

		if (mmy > uy)
			mmy = uy;
	}

	dr = new GlyphMat(mx - mmx, my - mmy);
	for (auto e : sd) {
		GlyphMat *m, *mm, *drr;
		int x, y;
		std::tie(m, mm, x, y) = e;
		drr = dr->copyMasked(m, mm, x - mmx, y - mmy);
		delete dr;
		delete m;
		delete mm;
		dr = drr;
	}

	return dr;
}

GlyphMat * Level::mergeUI(std::list<Drawable *> dl) {
	GlyphMat * dr;
	int mx = 0, my = 0, mmx = 0, mmy = 0;
	std::list<std::tuple<GlyphMat*, int, int>> sd;

	for (auto d : dl) {
		GlyphMat* dd = d->draw();
		int ux, uy;
		int uw, uh;
		std::tie(uw, uh) = dd->getSize();
		std::tie(ux, uy) = d->getPos();
		sd.push_back(std::make_tuple(dd, ux, uy));

		if (mx < ux + uw)
			mx = ux + uw;

		if (my < uy + uh)
			my = uy + uh;

		if (mmx > ux)
			mmx = ux;

		if (mmy > uy)
			mmy = uy;
	}

	dr = new GlyphMat(mx - mmx, my - mmy);
	for (auto e : sd) {
		GlyphMat* m, *drr;
		int x, y;
		std::tie(m, x, y) = e;
		drr = dr->copy(m, x - mmx, y - mmy, GlyphMat::COPY_OR);
		delete m;
		delete dr;
		dr = drr;
	}

	return dr;
}

GlyphMat * Level::mergeMasks(std::list<Drawable *> dl,
		GlyphMat::copyMode cm) {
	GlyphMat * dr;
	int mx = 0, my = 0, mmx = 0, mmy = 0;
	std::list<std::tuple<GlyphMat*, int, int>> sd;

	for (auto d : dl) {
		GlyphMat * dd = d->getMask();
		int ux, uy;
		int uw, uh;
		std::tie(uw, uh) = dd->getSize();
		std::tie(ux, uy) = d->getPos();
		sd.push_back(std::make_tuple(dd, ux, uy));

		if (mx < ux + uw)
			mx = ux + uw;

		if (my < uy + uh)
			my = uy + uh;

		if (mmx > ux)
			mmx = ux;

		if (mmy > uy)
			mmy = uy;
	}

	dr = new GlyphMat(mx - mmx, my - mmy);
	for (auto e : sd) {
		GlyphMat *m, *drr;
		int x, y;
		std::tie(m, x, y) = e;
		drr = dr->copy(m, x - mmx, y - mmy, cm);
		delete m;
		delete dr;
		dr = drr;
	}

	return dr;
}

std::tuple<int, int> Level::getSP(int fx, int fy, int tx, int ty) {
	if (fx == tx && fy == ty) {
		return std::make_tuple(0, 0);
	}
	std::tuple<int, int> ret;
	int ww, wh;
	std::tie(ww, wh) = this->worldMask->getSize();
        std::vector<std::vector<int>> dist;
	for (int i = 0; i < wh; i++) {
		dist.push_back(std::vector<int>(ww));
		for (int j = 0; j < ww; j++) {
			dist[i][j] = -1;
		}
	}
	dist[fy][fx] = 0;
	std::list<std::tuple<int,int>> queue;
	queue.push_front(std::make_tuple(fy, fx));
	int d[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
	while (!queue.empty()) {
		int ey, ex;
		std::tie(ey, ex)  = queue.back();
		queue.pop_back();
		for (int i = 0; i < 4; i++) {
			int ny = ey + d[i][0];
			int nx = ex + d[i][1];

			if (ny < wh && ny >= 0 && nx < ww && nx >= 0) {
				if (ny == ty && nx == tx) {
					dist[ny][nx] = dist[ey][ex] + 1;
					int sx, sy;
					while (ny != fy || nx != fx) {
						int cx = 0, cy = 0;
						int dmx = dist[ny][nx];
						for (i = 0; i < 4; i++) {
							int dy = ny + d[i][0];
							int dx = nx + d[i][1];
							if (dy >= wh || dy < 0 || dx >= ww || dx < 0) {
								break;
							}
							int dd = dist[dy][dx];
							if (dd < dmx && dd != -1) {
								dmx = dd;
								cy = dy;
								cx = dx;
							}
						}
						sx = nx;
						sy = ny;
						nx = cx;
						ny = cy;
					}
					ret = std::make_tuple(sy - fy, sx - fx);
					goto end;
				}

				if (this->worldMask->at(ny, nx) == 0 && dist[ny][nx] == -1) {
					dist[ny][nx] = dist[ey][ex] + 1;
					if (dist[ny][nx] <= 50) {
						queue.push_front(std::make_tuple(ny, nx));
					}
				}
			}
		}
	}

	ret = std::make_tuple(0, 0);
	end:
	return ret;
}

GameObject * Level::colides(GameObject * go) {
	for (auto g : this->gameObjects) {
		if (g == go)
			continue;
		if (!g->near(go))
			continue;
		if (g->intersects(go)) {
			return g;
		}
	}

	return nullptr;
}

GameObject * Level::onTop(GameObject * go) {
	for (auto g : this->gameObjects) {
		if (g == go)
			continue;
		if (!g->near(go))
			continue;
		if (g->onTop(go)) {
			return g;
		}
	}

	return nullptr;
}

GlyphMat * Level::draw() {
	this->script->tick();

	delete this->worldMask;
	this->worldMask = mergeMasks(ptrListConv<Drawable>(this->gameObjects),
			GlyphMat::COPY_OR);

	delete this->world;
	this->world = mergeWorld(ptrListConv<Drawable>(this->gameObjects));

	return mergeUI(ptrListConv<Drawable>(this->uiElements));
}

void Level::addGO(GameObject * go) {
	this->gameObjects.push_back(go);
}

void Level::delGO(GameObject * go) {
	auto i = this->gameObjects.begin();
	for (; i != this->gameObjects.end(); ++i) {
		if (*i == go) {
			this->gameObjects.erase(i);
			delete go;
			return;
		}
	}
}

size_t Level::lenGO() {
	return this->gameObjects.size();
}

GameObject * Level::getGO(size_t index) {
	return *std::next(this->gameObjects.begin(), index);
}

GameObject * Level::getGOByPos(int x, int y) {
	for (auto go : this->gameObjects) {
		if (go->getPos() == std::make_pair(x, y))
			return go;
	}

	return nullptr;
}

GameObject * Level::getNearGO(
		GameObject * go) {
	auto goi = onTop(go);
	if (goi != nullptr)
		return goi;

	int nx, ny, ox, oy;
	std::tie(ox, oy) = go->getPos();
	std::tie(nx, ny) = go->getOrientation();
	nx += ox;
	ny += oy;

	go->setPos(nx, ny);
	goi = onTop(go);
	go->setPos(ox, oy);
	if (goi != nullptr)
		return goi;

	return nullptr;
}

void Level::addUE(UIElement * ue) {
	this->uiElements.push_back(ue);
}

void Level::delUE(UIElement * ue) {
	auto end = this->uiElements.end();
	for (auto i = this->uiElements.begin(); i != end; ++i) {
		if (*i == ue) {
			this->uiElements.erase(i);
			delete *i;
			return;
		}
	}
}

size_t Level::lenUE() {
	return this->uiElements.size();
}

UIElement * Level::getUE(size_t index) {
	return *std::next(this->uiElements.begin(), index);
}

GlyphMat* Level::getWorld() {
	return this->world;
}

Netrom* Level::getGameEngine() {
	return this->gameEngine;
}

void Level::event(Event* e) {
	this->script->event(e);
	;
}

unsigned long long Level::getNextGOId() {
	this->nextGOId++;
	return this->nextGOId;
}

} /* namespace netrom */
