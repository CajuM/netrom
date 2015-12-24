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

#include <boost/filesystem.hpp>

#include "netrom.h"

namespace fs = boost::filesystem;

namespace netrom {

class Level {
public:
	virtual ~Level();
	Level(Netrom& gameEngine, std::string path);

	char** update();

private:
	std::vector<GameObject> gameObjects;
	char32_t** scene;
	int sceneX;
	int sceneY;
	Netrom* gameEngine;
	fs::path levelPath;
	PyScript *script;
};

} /* namespace netrom */

#endif /* SRC_LEVEL_H_ */
