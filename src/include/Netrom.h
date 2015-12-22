/*
 * Netrom.h
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#ifndef SRC_NETROM_H_
#define SRC_NETROM_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

namespace netrom {

class Netrom {
public:
	virtual ~Netrom();

	bool hasInitFailed();

	SDL_Renderer* getRen();
	SDL_Window* getWin();

	static Netrom* init();
	void poolEvents();
	void mainLoop();

private:
	Netrom();

	void panic(std::string msg);

	void draw(SDL_Texture *tex, int x, int y);
	void drawGlyph(std::string c, int x, int y);
	void drawGlyphMatrix();

	SDL_Window* win;
	SDL_Renderer* ren;
	bool initFailed;
	bool quit;
	TTF_Font* font;
	char32_t **glyphMatrix;
	int glyphMatrixX;
	int glyphMatrixY;
};

} /* namespace netrom */

#endif /* SRC_NETROM_H_ */
