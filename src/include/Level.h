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

#include "GameObject.h"
#include "Netrom.h"

namespace netrom {

class Level {
public:
	virtual ~Level();

	static Level* load(Netrom& gameEngine, std::string path);
private:
	Level(Netrom& gameEngine);

	std::vector<GameObject*> gameObjects;
	char32_t** scene;
	int sceneX;
	int sceneY;
	Netrom* gameEngine;
};

} /* namespace netrom */

#endif /* SRC_LEVEL_H_ */
