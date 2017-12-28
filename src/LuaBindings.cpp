/*
 * LuaBindings.cpp
 *
 *  Created on: Jan 3, 2016
 *      Author: mihai
 */

#include "netrom.h"
#include "Netrom.h"
#include "Level.h"
#include "Event.h"
#include "Scene.h"
#include "MsgBox.h"
#include "GameObject.h"

using namespace netrom;

extern "C" {
typedef struct {
	int x;
	int y;
} V2;

GlyphMat * GlyphMat_new(char **, int h);

GameObject * GameObject_new(Level * level, GlyphMat ** icon, GlyphMat ** mask,
		int licon);
void GameObject_setPos(GameObject * self, int x, int y);
V2 GameObject_getPos(GameObject * self);
int GameObject_getOrientationX(GameObject * self);
int GameObject_getOrientationY(GameObject * self);
void GameObject_setFrame(GameObject * self, int index);
void GameObject_move(GameObject * self, int x, int y);
void GameObject_setNormalSpeed(GameObject * self, double speed);
unsigned long long GameObject_getId(GameObject * self);
int GameObject_isNull(GameObject * self);

void Level_addGO(Level * self, GameObject * go);
void Level_delGO(Level * self, GameObject * go);
void Level_addUE(Level * self, UIElement * ue);
GameObject * Level_getGOByPos(Level * self, int x, int y);
GameObject * Level_getNearGO(Level * self, GameObject * go);
V2 Level_getSP(Level * self, int fx, int fy, int tx, int ty);

V2 Netrom_getMatrixSize(Netrom * self);

Scene * Scene_new(Level * level);

MsgBox * MsgBox_new(Level * level);
void MsgBox_msg(MsgBox * self, char * msg);

void UIElement_setPos(UIElement * self, int x, int y);
void UIElement_setSize(UIElement * self, int x, int y);
}

GlyphMat * GlyphMat_new(char ** a, int h) {
	return new netrom::GlyphMat(a, h);
}

GameObject * GameObject_new(Level * level, GlyphMat ** icon, GlyphMat ** mask,
		int licon) {
	std::vector<GlyphMat *> nicon;
	std::vector<GlyphMat *> nmask;
	int i;
	for (i = 0; i < licon; i++) {
		nicon.push_back(icon[i]);
		nmask.push_back(mask[i]);
	}

	return new GameObject(level, nicon, nmask);
}

V2 GameObject_getOrientation(GameObject * self) {
	V2 p;
	std::tie(p.x, p.y) = self->getOrientation();
	return p;
}

V2 GameObject_getPos(GameObject * self) {
	V2 ret;
	std::tie(ret.x, ret.y) = self->getPos();
	return ret;
}

void GameObject_setFrame(GameObject * self, int index) {
	self->setFrame(index);
}

int GameObject_isNull(GameObject * self) {
	return self->isNull();
}

void GameObject_setPos(GameObject * self, int x, int y) {
	self->setPos(x, y);
}

unsigned long long GameObject_getId(GameObject * self) {
	return self->getId();
}

void GameObject_move(GameObject * self, int x, int y) {
	self->move(x, y);
}

void GameObject_setNormalSpeed(GameObject * self, double speed) {
	self->setNormalSpeed(speed);
}

void Level_addGO(Level * self, GameObject * go) {
	self->addGO(go);
}

V2 Level_getSP(Level * self, int fx, int fy, int tx, int ty) {
	V2 res;

	try {
		auto rr = self->getSP(fx, fy, tx, ty);
		std::tie(res.y, res.x) = rr;
  } catch(std::exception &e) {
    std::cout << e.what() << "\"\n";
  }

	return res;
}

GameObject * Level_getNearGO(Level * self, GameObject * go) {
	return self->getNearGO(go);
}

GameObject * Level_getGOByPos(Level * self, int x, int y) {
	return self->getGOByPos(x, y);
}

void Level_delGO(Level * self, GameObject * go) {
	self->delGO(go);
}

void Level_addUE(Level * self, UIElement * ue) {
	self->addUE(ue);
}

V2 Netrom_getMatrixSize(Netrom * self) {
	V2 s;
	int x, y;
	std::tie(x, y) = self->getMatrixSize();
	s.x = x;
	s.y = y;
	return s;
}

Scene * Scene_new(Level * level) {
	return new Scene(level);
}

MsgBox * MsgBox_new(Level * level) {
	return new netrom::MsgBox(level);
}

void MsgBox_msg(MsgBox * self, char * msg) {
	self->msg(std::string(msg));
}


void UIElement_setPos(UIElement * self, int x, int y) {
	self->setPos(x, y);
}

void UIElement_setSize(UIElement * self, int x, int y) {
	self->setSize(x, y);
}
