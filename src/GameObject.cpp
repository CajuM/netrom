/*
 * GameObject.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#include "GameObject.h"

namespace netrom {

GameObject::GameObject(netrom::Level * level,
		std::vector<netrom::GlyphMat *> icon,
		std::vector<netrom::GlyphMat *> mask) {
	this->level = level;
	this->icon = icon;
	this->mask = mask;
	this->frame = 0;
	this->x = 0;
	this->y = 0;
	this->orientationX = 0;
	this->orientationY = 1;
	this->speed = 0;
	this->maxSpeed = 0;
	this->normalSpeed = 0;
	this->maxWidth = 0;
	this->maxHeight = 0;
	this->id = this->level->getNextGOId();
	for (auto i : this->mask) {
		int w, h;
		std::tie(w, h) = i->getSize();
		if (w > this->maxWidth)
			this->maxWidth = w;
		if (h > this->maxHeight)
			this->maxHeight = h;
	}
}

GameObject::GameObject() {
	this->level = nullptr;
	this->frame = 0;
	this->x = 0;
	this->y = 0;
	this->orientationX = 0;
	this->orientationY = 1;
	this->speed = 0;
	this->maxSpeed = 0;
	this->normalSpeed = 0;
	this->maxWidth = 0;
	this->maxHeight = 0;
	this->id = 0;
}

GameObject::~GameObject() {
	for (auto e: this->icon) {
		delete e;
	}

	for (auto e: this->mask) {
		delete e;
	}
}

std::tuple<int, int, int, int> GameObject::getBounds() {
	return std::make_tuple(this->y, this->y + this->maxHeight - 1, this->x,
			this->x + this->maxWidth - 1);
}

void GameObject::setFrame(int frame) {
	this->frame = frame;
}

GlyphMat * GameObject::draw() {
	return new GlyphMat(this->icon[this->frame]);
}

GlyphMat * GameObject::getMask() {
	return new GlyphMat(this->mask[this->frame]);
}

std::pair<int, int> GameObject::getPos() {
	return std::make_pair(this->x, this->y);
}

void GameObject::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}

void GameObject::setOrientation(int x, int y) {
	this->orientationX = x;
	this->orientationY = y;
}

std::tuple<int, int> GameObject::getOrientation() {
	return std::make_tuple(this->orientationX, this->orientationY);
}

void GameObject::move(int x, int y) {
	int ox = this->x;
	int oy = this->y;
	this->x += this->normalSpeed * x;
	this->y += this->normalSpeed * y;
	auto cgo = this->level->colides(this);
	if (cgo) {
		this->x = ox;
		this->y = oy;
		this->level->event(new CollisionEvent(this->id, cgo->id));
	} else {
		setOrientation(x, y);
	}
}

void GameObject::setNormalSpeed(double speed) {
	this->normalSpeed = speed;
}

bool GameObject::near(GameObject* go) {
	int up1, lo1, le1, ri1;
	int up2, lo2, le2, ri2;
	std::tie(up1, lo1, le1, ri1) = this->getBounds();
	std::tie(up2, lo2, le2, ri2) = go->getBounds();
	if (!((up1 <= up2 && up2 <= lo1) || (up1 <= lo2 && lo2 <= lo1)))
		return false;
	if (!((le1 <= le2 && le2 <= ri1) || (le1 <= ri2 && ri2 <= ri1)))
		return false;
	return true;
}

bool GameObject::intersects(GameObject* go) {
	int i, j;
	int x1, y1, w1, h1;
	int x2, y2, w2, h2;

	bool ret = false;

	std::tie(x1, y1) = this->getPos();
	GlyphMat * m1 = this->getMask();
	std::tie(w1, h1) = m1->getSize();
	std::tie(x2, y2) = go->getPos();
	GlyphMat * m2 = go->getMask();
	std::tie(w2, h2) = m2->getSize();

	for (i = 0; i < h1; i++) {
		if (((y1 + i) >= (y2 + h2)) || ((y1 + i) < y2))
			continue;
		for (j = 0; j < w1; j++) {
			if (((x1 + j) >= (x2 + w2)) || ((x1 + j) < x2))
				continue;
			if (!(std::iswspace(m1->at(i, j)) || std::iswspace(m2->at(y1 + i - y2, x1 + j - x2)))) {
				ret = true;
				goto end;
			}

		}
	}
end:
	delete m1;
	delete m2;

	return ret;
}

bool GameObject::onTop(GameObject* go) {
	int i, j;
	int x1, y1, w1, h1;
	int x2, y2, w2, h2;

	bool ret= false;

	std::tie(x1, y1) = this->getPos();
	GlyphMat* m1 = this->draw();
	std::tie(w1, h1) = m1->getSize();
	std::tie(x2, y2) = go->getPos();
	GlyphMat* m2 = go->draw();
	std::tie(w2, h2) = m2->getSize();

	for (i = 0; i < h1; i++) {
		if (((y1 + i) >= (y2 + h2)) || ((y1 + i) < y2))
			continue;
		for (j = 0; j < w1; j++) {
			if (((x1 + j) >= (x2 + w2)) || ((x1 + j) < x2))
				continue;
			if (!(std::iswspace(m1->at(i, j)) || std::iswspace(m2->at(y1 + i - y2, x1 + j - x2)))) {
				ret = true;
				goto end;
			}
		}
	}
end:
	delete m1;
	delete m2;

	return ret;
}

unsigned long long GameObject::getId() {
	return this->id;
}

bool GameObject::isNull() {
	return this->level == nullptr;
}

} /* namespace netrom */
