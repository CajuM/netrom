/*
 * Netrom.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#include "Netrom.h"

#include <iostream>
#include <cstdlib>
#include <locale>
#include <utility>
#include <codecvt>

namespace netrom {

Netrom::Netrom(int argc, char ** argv) {
	if (argc == 2 && std::string(argv[1]) == "-d") {
		std::cout << "Debugging enabled" << std::endl;
		this->debug = true;
	} else {
		this->debug = false;
	}

	this->initFailed = false;

	char * str = SDL_GetBasePath();
	this->root = fs::path(str).parent_path().parent_path();
	free(str);

	this->res = this->root / "share" / "netrom";

	this->lib = this->root / "lib";

	this->quit = false;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		this->initFailed = true;
	}

	if (TTF_Init() != 0) {
		std::cout << "TTF_Init" << std::endl;
		this->initFailed = true;
	}

	this->fontSize = 18;
	font = TTF_OpenFont(
			(this->res / "fonts" / "Monospace.ttf").native().c_str(),
			this->fontSize);
	if (font == nullptr) {
		std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
		this->initFailed = true;
	}
	TTF_SizeUTF8(font, "A", &(this->glyphWidth), &(this->glyphHeight));

	this->screenWidth = 80;
	this->screenHeight = 30;

	this->win = SDL_CreateWindow("Hello World!", 100, 100,
			this->screenWidth * this->glyphWidth,
			this->screenHeight * this->glyphHeight, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		this->initFailed = true;
	}

	this->ren = SDL_CreateRenderer(win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError()
				<< std::endl;
		this->initFailed = true;
	}

	this->currentLevel = new Level(this, "intro");
}

Netrom::~Netrom() {
	delete this->currentLevel;
	TTF_CloseFont(this->font);
	SDL_DestroyRenderer(this->ren);
	SDL_DestroyWindow(this->win);
	SDL_Quit();
}

Netrom* Netrom::init(int argc, char ** argv) {
	Netrom* netrom = new Netrom(argc, argv);
	if (netrom->hasInitFailed()) {
		delete netrom;
		exit(1);
	}
	return netrom;
}

bool Netrom::hasInitFailed() {
	return this->initFailed;
}

SDL_Renderer* Netrom::getRen() {
	return this->ren;
}

SDL_Window* Netrom::getWin() {
	return this->win;
}

void Netrom::draw(SDL_Texture *tex, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(this->ren, tex, NULL, &dst);
	SDL_DestroyTexture(tex);
}

void Netrom::drawGlyph(std::string c, int x, int y) {
	if (c.empty())
		return;

	SDL_Color color = { 255, 255, 255, 255 };

	SDL_Surface *surf = TTF_RenderUTF8_Blended(this->font, c.c_str(), color);
	if (surf == nullptr) {
		panic("TTF_RenderText");
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->ren, surf);
	if (texture == nullptr) {
		panic("CreateTexture");
	}

	SDL_FreeSurface(surf);

	draw(texture, x * this->glyphWidth, y * this->glyphHeight);
}

void Netrom::poolEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			this->quit = true;
		}

		if (e.type == SDL_KEYDOWN) {
			std::string state = e.key.type == SDL_KEYDOWN ? "down" : "up";
			std::string name = SDL_GetKeyName(e.key.keysym.sym);
			Event* ev = new KbdEvent(state, name);
			this->currentLevel->event(ev);
		}
	}
}

void Netrom::mainLoop() {
	while (true) {
		if (this->quit)
			break;
		SDL_RenderClear(this->ren);
		poolEvents();
		drawGlyphMatrix(this->currentLevel->draw());
		SDL_RenderPresent(this->ren);
		SDL_Delay(100);
	}
}

void Netrom::panic(std::string msg) {
	std::cout << msg << std::endl;
	this->quit = true;
}

void Netrom::drawGlyphMatrix(GlyphMat m) {
	int i, j;
	int x, y;
	std::tie(x, y) = m.getSize();
	for (i = 0; i < y; i++) {
		for (j = 0; j < x; j++) {
			char32_t *str = new char32_t[2];
			std::u32string source;
			std::string dest;
			char32_t c = m.at(i, j);
			str[0] = c;
			str[1] = U'\0';
			source = str;
			delete[] str;
			dest = conv::utf_to_utf<char>(source);
			drawGlyph(dest, j, i);
		}
	}
}

fs::path Netrom::getRes() {
	return this->res;
}

fs::path Netrom::getLib() {
	return this->lib;
}

void Netrom::del(Netrom *gameEngine) {
	delete gameEngine;
}

std::tuple<int, int> Netrom::getMatrixSize() {
	return std::make_tuple(this->screenWidth, this->screenHeight);
}

bool Netrom::debugEnabled() {
	return this->debug;
}

} /* namespace netrom */
