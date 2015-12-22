/*
 * Level.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#include "Level.h"

namespace netrom {

Level::Level(Netrom& gameEngine) {
	this->gameEngine = &gameEngine;
	this->sceneX = 10000;
	this->sceneY = 10000;
	this->scene = new char32_t*[sceneY];
	int i, j;
	for (i = 0; i < this->sceneY; i++) {
		this->scene[i] = new char32_t[sceneX];
		for (j = 0; j < this->sceneX; j++)
			this->scene[j] = '\0';
	}
}

Level::~Level() {
	// TODO Auto-generated destructor stub
}

Level* Level::load(Netrom& gameEngine, std::string path) {
	Level *l = new Level(gameEngine);
	return l;
}

} /* namespace netrom */
