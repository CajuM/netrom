/*
 * Scene.cpp
 *
 *  Created on: Dec 26, 2015
 *      Author: mihai
 */

#include "Scene.h"

namespace netrom {

Scene::Scene(Level* level) : UIElement(level) {
	this->worldX = 0;
	this->worldY = 0;
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

GlyphMat Scene::draw() {
	size_t i, j;
	GlyphMat world = this->level->getWorld();
	int ww, wh;
	std::tie(ww, wh) = world.getSize();
	GlyphMat dr(this->width, this->height, U'\0');
	for (i = 0; i < this->height; i++)
		for (j = 0; j < this->width; j++) {
			int ni = this->worldY + i;
			int nj = this->worldX + j;
			if (ni < wh && ni >= 0 && nj < ww && nj >= 0)
				dr.at(i, j) = world.at(ni, nj);
		}
	return dr;
}

void Scene::event(SDL_Event* e) {

}

} /* namespace netrom */
