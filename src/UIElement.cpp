/*
 * UIElement.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#include "UIElement.h"

namespace netrom {

UIElement::UIElement(Level* level) {
	this->x = 0;
	this->y = 0;
	this->height = 0;
	this->width = 0;
	this->level = level;
}

UIElement::~UIElement() {
	// TODO Auto-generated destructor stub
}

std::pair<int, int> UIElement::getPos() {
	return std::pair<int, int>(this->x, this->y);
}

std::pair<int, int> UIElement::getSize() {
	return std::pair<int, int>(this->width, this->height);
}

void UIElement::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

void UIElement::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}

} /* namespace netrom */
