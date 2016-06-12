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

#include "netrom.h"
#include "Level.h"
#include "GlyphMat.h"
#include "Event.h"

namespace netrom {

class Netrom {
public:
	bool hasInitFailed();

	SDL_Renderer* getRen();
	SDL_Window* getWin();
	fs::path getRes();
	fs::path getLib();

	std::tuple<int, int> getMatrixSize();

	static netrom::Netrom* init(int argc, char ** argv);
	static void del(Netrom *gameEngine);

	void poolEvents();
	void mainLoop();

	bool debugEnabled();
private:
	Netrom(int argc, char ** argv);
	virtual ~Netrom();

	void panic(std::string msg);

	void draw(SDL_Texture *tex, int x, int y);
	void drawGlyph(std::string c, int x, int y);
	void drawGlyphMatrix(GlyphMat m);

	SDL_Window* win;
	SDL_Renderer* ren;
	bool initFailed;
	bool quit;
	TTF_Font* font;
	int screenWidth;
	int screenHeight;
	fs::path root;
	fs::path res;
	fs::path lib;
	netrom::Level *currentLevel;
	int fontSize;
	int glyphWidth;
	int glyphHeight;

	bool debug;
};

} /* namespace netrom */

#endif /* SRC_NETROM_H_ */
