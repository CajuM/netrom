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

Level::Level(Netrom* gameEngine, std::string name) {
	this->world = GlyphMat();
	this->nextGOId = 0;
	this->gameEngine = gameEngine;
	this->levelPath = this->gameEngine->getRes() / "levels" / name
			/ (name + ".lua");
	this->script = new LuaScript(this, this->levelPath);
	this->script->load();
}

Level::~Level() {
	delete this->script;
}

GlyphMat Level::mergeWorld(std::list<std::shared_ptr<Drawable>> dl) {
	GlyphMat dr;
	int mx = 0, my = 0, mmx = 0, mmy = 0;
	std::list<std::tuple<GlyphMat, GlyphMat, int, int>> sd;

	for (auto d : dl) {
		GlyphMat dd = d->draw();
		int ux, uy;
		int uw, uh;
		std::tie(uw, uh) = dd.getSize();
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

	dr = GlyphMat(mx - mmx, my - mmy);
	for (auto e : sd) {
		GlyphMat m, mm;
		int x, y;
		std::tie(m, mm, x, y) = e;
		dr = dr.copyMasked(m, mm, x - mmx, y - mmy);
	}
	return dr;
}

GlyphMat Level::mergeUI(std::list<std::shared_ptr<Drawable>> dl) {
	GlyphMat dr;
	int mx = 0, my = 0, mmx = 0, mmy = 0;
	std::list<std::tuple<GlyphMat, int, int>> sd;

	for (auto d : dl) {
		GlyphMat dd = d->draw();
		int ux, uy;
		int uw, uh;
		std::tie(uw, uh) = dd.getSize();
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

	dr = GlyphMat(mx - mmx, my - mmy);
	for (auto e : sd) {
		GlyphMat m;
		int x, y;
		std::tie(m, x, y) = e;
		dr = dr.copy(m, x - mmx, y - mmy, GlyphMat::COPY_OR);
	}
	return dr;
}

GlyphMat Level::mergeMasks(std::list<std::shared_ptr<Drawable>> dl,
		GlyphMat::copyMode cm) {
	GlyphMat dr;
	int mx = 0, my = 0, mmx = 0, mmy = 0;
	std::list<std::tuple<GlyphMat, int, int>> sd;

	for (auto d : dl) {
		GlyphMat dd = d->getMask();
		int ux, uy;
		int uw, uh;
		std::tie(uw, uh) = dd.getSize();
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

	dr = GlyphMat(mx - mmx, my - mmy);
	for (auto e : sd) {
		GlyphMat m;
		int x, y;
		std::tie(m, x, y) = e;
		dr = dr.copy(m, x - mmx, y - mmy, cm);
	}
	return dr;
}

std::tuple<int, int> Level::getSP(int fx, int fy, int tx, int ty) {
	if (fx == tx && fy == ty) {
		return std::make_tuple(0, 0);
	}
	std::tuple<int, int> ret;
	int ww, wh;
	std::tie(ww, wh) = this->worldMask.getSize();
	int ** dist = new int*[wh];
	for (int i = 0; i < wh; i++) {
		dist[i] = new int[ww];
		for (int j = 0; j < ww; j++) {
			dist[i][j] = -1;
		}
	}
	dist[fy][fx] = 0;
	std::list<int*> queue;
	queue.push_front(new int[2] { fy, fx });
	int d[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
	while (!queue.empty()) {
		int * el = queue.back();
		queue.pop_back();
		int ey = el[0];
		int ex = el[1];
		delete el;
		for (int i = 0; i < 4; i++) {
			int ny = ey + d[i][0];
			int nx = ex + d[i][1];

			if (ny < wh && ny >= 0 && nx < ww && nx >= 0) {
				if (ny == ty && nx == tx) {
					std::cout << "vodka" << std::endl;
					int sx, sy;
					while (ny != fy && nx != fx) {
						int cx = 0, cy = 0;
						int dmx = dist[ny][nx];
						for (i = 0; i < 4; i++) {
							int dy = ny + d[i][0];
							int dx = nx + d[i][1];
							if (dy >= wh || dy < 0 || dx >= ww || dx < 0) {
								break;
							}
							int dd = dist[dy][dx];
							if (dd < dmx) {
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

				if (this->worldMask.at(ny, nx) == 0 && dist[ny][nx] == -1) {
					dist[ny][nx] = dist[ey][ex] + 1;
					if (dist[ny][nx] <= 50) {
						queue.push_front(new int[2] { ny, nx });
					}
				}
			}
		}
	}

	ret = std::make_tuple(0, 0);
	end: for (int i = 0; i < wh; i++) {
		for (int j = 0; j < ww; j++) {
			std::cout << dist[i][j] << " ";
		}
		std::cout << std::endl;
	}

	while (!queue.empty()) {
		auto el = queue.back();
		delete el;
		queue.pop_back();
	}

	for (int i = 0; i < wh; i++) {
		delete dist[i];
	}
	delete dist;

	return ret;
}

std::shared_ptr<GameObject> Level::colides(GameObject* go) {
	for (auto g : this->gameObjects) {
		if (g.get() == go)
			continue;
		if (!g->near(go))
			continue;
		if (g->intersects(go)) {
			return g;
		}
	}
	return std::shared_ptr < GameObject > (nullptr);
}

std::shared_ptr<GameObject> Level::onTop(GameObject* go) {
	for (auto g : this->gameObjects) {
		if (g.get() == go)
			continue;
		if (!g->near(go))
			continue;
		if (g->onTop(go)) {
			return g;
		}
	}
	return std::shared_ptr < GameObject > (nullptr);
}

GlyphMat Level::draw() {
	this->script->tick();
	this->worldMask = mergeMasks(ptrListConv<Drawable>(this->gameObjects),
			GlyphMat::COPY_OR);
	this->world = mergeWorld(ptrListConv<Drawable>(this->gameObjects));
	return mergeUI(ptrListConv<Drawable>(this->uiElements));
}

void Level::addGO(std::shared_ptr<GameObject> go) {
	this->gameObjects.push_back(go);
}

void Level::delGO(std::shared_ptr<GameObject> go) {
	auto i = this->gameObjects.begin();
	for (; i != this->gameObjects.end(); ++i) {
		if (*i == go)
			break;
	}

	if (i == this->gameObjects.end())
		return;

	this->gameObjects.erase(i);
}

size_t Level::lenGO() {
	return this->gameObjects.size();
}

std::shared_ptr<GameObject> Level::getGO(size_t index) {
	return *std::next(this->gameObjects.begin(), index);
}

std::shared_ptr<netrom::GameObject> Level::getGOByPos(int x, int y) {
	for (auto go : this->gameObjects) {
		if (go->getPos() == std::make_pair(x, y))
			return go;
	}
	return std::shared_ptr < netrom::GameObject > (new GameObject());
}

std::shared_ptr<netrom::GameObject> Level::getNearGO(
		std::shared_ptr<netrom::GameObject> go) {
	auto goi = onTop(go.get());
	if (goi != nullptr)
		return goi;

	int nx, ny, ox, oy;
	std::tie(ox, oy) = go->getPos();
	std::tie(nx, ny) = go->getOrientation();
	nx += ox;
	ny += oy;

	go->setPos(nx, ny);
	goi = onTop(go.get());
	go->setPos(ox, oy);
	if (goi != nullptr)
		return goi;

	return std::shared_ptr < netrom::GameObject > (new GameObject());
}

void Level::addUE(std::shared_ptr<UIElement> ue) {
	this->uiElements.push_back(ue);
}

void Level::delUE(size_t index) {
	this->uiElements.erase(std::next(this->uiElements.begin(), index));
}

size_t Level::lenUE() {
	return this->uiElements.size();
}

std::shared_ptr<UIElement> Level::getUE(size_t index) {
	return *std::next(this->uiElements.begin(), index);
}

void Level::newWorld(size_t width, size_t height) {
	this->world = GlyphMat(width, height);
}

const GlyphMat Level::getWorld() {
	return this->world;
}

netrom::Netrom* Level::getGameEngine() {
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
