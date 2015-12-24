/*
 * GameObjectList.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#include "GameObjectList.h"

namespace netrom {

GameObjectList::GameObjectList(std::vector<GameObject>& gameObjects) {
	this->gameObjects = &gameObjects;
	this->distructable = false;
}

GameObjectList::GameObjectList() {
	this->gameObjects = new std::vector<GameObject>;
	this->distructable = true;
}

GameObjectList::~GameObjectList() {
	if (this->distructable)
		delete this->gameObjects;
}

void GameObjectList::__delitem__(size_t key) {
	this->gameObjects->erase(this->gameObjects->begin() + key);
}

GameObject& GameObjectList::__getitem__(size_t key) {
	return (*this->gameObjects)[key];
}

void GameObjectList::__setitem__(size_t key, GameObject& gameObject) {
	(*this->gameObjects)[key] = gameObject;
}

size_t GameObjectList::__len__() {
	return this->gameObjects->size();
}

void GameObjectList::append(GameObject gameObject) {
	this->gameObjects->push_back(gameObject);
}

GameObjectList::operator py::object() {
	return py::object(*this);
}

} /* namespace netrom */
