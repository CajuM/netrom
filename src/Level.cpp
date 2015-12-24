/*
 * Level.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#include "Level.h"

namespace netrom {

Level::Level(Netrom& gameEngine, std::string name) {
	this->gameEngine = &gameEngine;
	this->levelPath = this->gameEngine->getRes() / "levels" / name / (name + ".py");
	this->script = new PyScript(gameEngine, this->levelPath);
	this->script->bind("gameObjects", this->script->toPythonList(this->gameObjects));
	this->script->init();
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
	this->script->del(this->script);
	int i;
	for (i = 0; i < this->sceneY; i++)
		delete[] this->scene[i];
	delete[] this->scene;
}

char** Level::update() {
	return nullptr;
}

} /* namespace netrom */
