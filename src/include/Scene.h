/*
 * Scene.h
 *
 *  Created on: Dec 26, 2015
 *      Author: mihai
 */

#ifndef SRC_SCENE_H_
#define SRC_SCENE_H_

#include "netrom.h"
#include "UIElement.h"
#include "GameObject.h"

namespace netrom {

class Scene : public UIElement {
public:
	Scene(Level* level);
	virtual ~Scene();

	netrom::GlyphMat draw();
	void event(SDL_Event* e);

private:
	int worldX;
	int worldY;
};
} /* namespace netrom */

#endif /* SRC_SCENE_H_ */
