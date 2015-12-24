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

#include <boost/filesystem.hpp>
#include <boost/python.hpp>

#include <Python.h>

#include "netrom.h"

namespace fs = boost::filesystem;
namespace py = boost::python;

namespace netrom {

class Netrom {
public:
	bool hasInitFailed();

	SDL_Renderer* getRen();
	SDL_Window* getWin();
	fs::path getRes();
	fs::path getLib();
	py::object getPyGlobalNamespace();

	static Netrom* init();
	static void del(Netrom *gameEngine);

	void poolEvents();
	void mainLoop();

private:
	Netrom();
	virtual ~Netrom();

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
	fs::path root;
	fs::path res;
	fs::path lib;
	netrom::Level *currentLevel;
};

} /* namespace netrom */

#endif /* SRC_NETROM_H_ */
