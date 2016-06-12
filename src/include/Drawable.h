/*
 * Drawable.h
 *
 *  Created on: Dec 26, 2015
 *      Author: mihai
 */

#ifndef SRC_DRAWABLE_H_
#define SRC_DRAWABLE_H_

#include "GlyphMat.h"

namespace netrom {

class Drawable {
public:
	virtual ~Drawable() {}

	virtual netrom::GlyphMat draw() = 0;
	virtual netrom::GlyphMat getMask() {return netrom::GlyphMat();}
	virtual std::pair<int, int> getPos() = 0;
	virtual void setPos(int x, int y) = 0;
};

} /* namespace netrom */

#endif /* SRC_DRAWABLE_H_ */
