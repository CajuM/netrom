/*
 * MsgBox.h
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#ifndef SRC_INCLUDE_MSGBOX_H_
#define SRC_INCLUDE_MSGBOX_H_

#include <tuple>
#include <memory>

#include "netrom.h"
#include "UIElement.h"
#include "GlyphMat.h"

namespace netrom {

class MsgBox : public UIElement {
public:
	MsgBox(Level* level);
	virtual ~MsgBox();

	void msg(std::string msg);

	netrom::GlyphMat draw();

	void event(SDL_Event* e);

	static std::shared_ptr<netrom::MsgBox> get(Level* level);

	void setSize(int x, int y);

private:
	void pushString(std::u32string s);
	void pushChar(char32_t c);

	int scroll;

	std::vector<std::u32string> msgV;

	int innerWidth;
	int innerHeight;
};

} /* namespace netrom */

#endif /* SRC_INCLUDE_MSGBOX_H_ */
