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
#include <memory>

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
	Level(netrom::Netrom* gameEngine, std::string path);

	netrom::GlyphMat draw();

	void addGO(std::shared_ptr<netrom::GameObject> go);
	void delGO(std::shared_ptr<netrom::GameObject> go);
	size_t lenGO();
	std::shared_ptr<netrom::GameObject>  getGO(size_t index);
	std::shared_ptr<netrom::GameObject>  getGOByPos(int x, int y);
	std::shared_ptr<netrom::GameObject>  getNearGO(std::shared_ptr<netrom::GameObject> go);
	std::tuple<int, int>  getSP(int fx, int fy, int tx, int ty);

	void addUE(std::shared_ptr<netrom::UIElement>  go);
	void delUE(size_t index);
	size_t lenUE();
	std::shared_ptr<netrom::UIElement>  getUE(size_t index);

	void newWorld(size_t width, size_t height);
	const netrom::GlyphMat getWorld();

	netrom::Netrom* getGameEngine();

	void event(Event* e);

	std::shared_ptr<GameObject> colides(GameObject* go);
	std::shared_ptr<GameObject> onTop(GameObject* go);

	unsigned long long getNextGOId();

private:
	void update();
	netrom::GlyphMat mergeWorld(std::list<std::shared_ptr<Drawable>> dl);
	netrom::GlyphMat mergeUI(std::list<std::shared_ptr<Drawable>> dl);
	netrom::GlyphMat mergeMasks(std::list<std::shared_ptr<Drawable>> dl, netrom::GlyphMat::copyMode cm);

	std::list<std::shared_ptr<netrom::GameObject>> gameObjects;
	std::list<std::shared_ptr<netrom::UIElement>> uiElements;
	netrom::Netrom* gameEngine;
	fs::path levelPath;
	netrom::GlyphMat world;
	netrom::GlyphMat worldMask;
	netrom::LuaScript* script;
	unsigned long long nextGOId;
};

} /* namespace netrom */

#endif /* SRC_LEVEL_H_ */
