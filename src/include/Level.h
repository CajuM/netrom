/*
 * Level.h
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include <vector>
#include <string>
#include <tuple>
#include <list>

#include "netrom.h"
#include "Netrom.h"
#include "UIElement.h"
#include "GameObject.h"
#include "GlyphMat.h"
#include "LuaScript.h"
#include "Event.h"

namespace netrom {

class Level {
public:
	virtual ~Level();
	Level(Netrom* gameEngine, std::string path);

	GlyphMat * draw();

	void addGO(GameObject * go);
	void delGO(GameObject * go);
	size_t lenGO();
	GameObject *  getGO(size_t index);
	GameObject *  getGOByPos(int x, int y);
	GameObject *  getNearGO(GameObject * go);
	std::tuple<int, int>  getSP(int fx, int fy, int tx, int ty);

	void addUE(UIElement * ue);
	void delUE(UIElement * ue);
	size_t lenUE();
	UIElement * getUE(size_t index);

	GlyphMat * getWorld();

	Netrom * getGameEngine();

	void event(Event* e);

	GameObject * colides(GameObject * go);
	GameObject * onTop(GameObject * go);

	unsigned long long getNextGOId();

private:
	void update();
	GlyphMat * mergeWorld(std::list<Drawable *> dl);
	GlyphMat * mergeUI(std::list<Drawable *> dl);
	GlyphMat * mergeMasks(std::list<Drawable *> dl, GlyphMat::copyMode cm);

	std::list<GameObject *> gameObjects;
	std::list<UIElement *> uiElements;
	Netrom * gameEngine;
	fs::path levelPath;
	GlyphMat * world;
	GlyphMat * worldMask;
	LuaScript * script;
	unsigned long long nextGOId;
};

} /* namespace netrom */

#endif /* SRC_LEVEL_H_ */
