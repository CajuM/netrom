/*
 * UIElement.h
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#ifndef SRC_UIELEMENT_H_
#define SRC_UIELEMENT_H_

#include <tuple>

#include <SDL2/SDL.h>

#include "netrom.h"
#include "Level.h"
#include "Drawable.h"

namespace netrom {

class UIElement : public Drawable {
public:
	UIElement(Level* level);
	virtual ~UIElement();

	virtual void event(SDL_Event* e) = 0;

	std::pair<int, int> getPos();
	virtual void setPos(int x, int y);

	std::pair<int, int> getSize();
	virtual void setSize(int x, int y);

protected:
	int x, y;
	size_t width, height;
	Level* level;
};

} /* namespace netrom */

#endif /* SRC_UIELEMENT_H_ */
