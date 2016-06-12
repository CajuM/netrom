/*
 * MsgBox.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#include <MsgBox.h>

namespace netrom {

MsgBox::MsgBox(Level* level) : UIElement(level){
	this->scroll = 0;
	this->width = 0;
	this->height = 0;
	this->innerWidth = this->width - 2;
	this->innerHeight = this->height -2;
}

MsgBox::~MsgBox() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<netrom::MsgBox> MsgBox::get(Level* level) {
	return std::shared_ptr<netrom::MsgBox>(new netrom::MsgBox(level));
}

void MsgBox::msg(std::string msg) {
	this->msgV.push_back(std::u32string());
	std::u32string msg4 = conv::utf_to_utf<char32_t>(msg);
	size_t i = 0;
	while (i < msg4.length()) {
		while(std::iswspace(msg4[i]) && i < msg4.length()) {
			pushChar(msg4[i++]);
		}
		int begin = i;
		while(!std::iswspace(msg4[i]) && i < msg4.length()) {
			i++;
		}
		int end = i;
		int len = end - begin;
		std::u32string ss = msg4.substr(begin, len);
		if (this->msgV[this->msgV.size() - 1].length() + len > this->innerWidth)
			this->msgV.push_back(std::u32string());
		pushString(ss);
	}
	this->scroll = this->msgV.size() - this->innerHeight;
	this->scroll = this->scroll > 0 ? this->scroll : 0;
}

void MsgBox::pushChar(char32_t c) {
	auto lastLine = this->msgV.end() - 1;
	if (lastLine->length() >= this->innerWidth) {
		this->msgV.push_back(std::u32string());
		lastLine = this->msgV.end() - 1;
	}
	if (c == '\n') {
		this->msgV.push_back(std::u32string());
	} else {
		lastLine->push_back(c);
	}
}

void MsgBox::pushString(std::u32string s) {
	int i;
	for (i = 0; i < s.length(); i++)
		pushChar(s[i]);
}

void MsgBox::event(SDL_Event* e) {

}

GlyphMat MsgBox::draw() {
	if (this->width == 0 || this->height == 0)
		return GlyphMat();

	int i;
	GlyphMat dr(this->width, this->height);

	dr.at(0, 0) = U'╔';
	for (i = 1; i < this->width - 1; i++)
		dr.at(0, i) = U'═';
	dr.at(0, this->width - 1) = U'╗';

	for (i = 1; i < this->height - 1; i++) {
		dr.at(i, 0) = U'║';
		int mi = this->scroll + i - 1;
		int j;
		std::u32string& str = this->msgV[mi];
		for (j = 1; j < this->width; j++)
			if (mi < this->msgV.size() && j <= str.length()) {
				dr.at(i, j) = str[j - 1];
			} else {
				dr.at(i, j) = U'\0';
			}
		dr.at(i, this->width - 1) = U'║';
	}
	dr.at(this->height - 1, 0) = U'╚';
	for (i = 1; i < this->width - 1; i++)
		dr.at(this->height - 1, i) = U'═';
	dr.at(this->height - 1, this->width - 1) = U'╝';

	return dr;
}

void MsgBox::setSize(int x, int y) {
	this->width = x;
	this->height = y;
	this->innerWidth = x - 2;
	this->innerHeight = y - 2;
}

} /* namespace netrom */
