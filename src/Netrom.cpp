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

Netrom::Netrom() {
	this->initFailed = false;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		this->initFailed = true;
	}

	this->win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480,
			SDL_WINDOW_SHOWN);
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

	if (TTF_Init() != 0) {
		std::cout << "TTF_Init" << std::endl;
		this->initFailed = true;
	}

	font = TTF_OpenFont("../res/unifont_csur-8.0.01.ttf", 20);
	if (font == nullptr) {
		std::cout << "TTF_OpenFont" << std::endl;
		this->initFailed = true;
	}

	this->quit = false;

	this->glyphMatrixX = 640 / 10;
	this->glyphMatrixY = 480 / 20;

	this->glyphMatrix = new char32_t*[this->glyphMatrixY];
	int i;
	for (i = 0; i < this->glyphMatrixY; i++) {
		this->glyphMatrix[i] = new char32_t[this->glyphMatrixX];
		int j;
		for (j = 0; j < this->glyphMatrixX; j++)
			this->glyphMatrix[i][j] = '\0';
	}
}

Netrom::~Netrom() {
	TTF_CloseFont(this->font);
	SDL_DestroyRenderer(this->ren);
	SDL_DestroyWindow(this->win);
	SDL_Quit();
}

Netrom* Netrom::init() {
	Netrom* netrom = new Netrom();
	if (netrom->hasInitFailed()) {
		delete netrom;
		SDL_Quit();
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

	SDL_Surface *surf = TTF_RenderText_Blended(this->font, c.c_str(), color);
	if (surf == nullptr) {
		panic("TTF_RenderText");
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->ren, surf);
	if (texture == nullptr) {
		panic("CreateTexture");
	}

	SDL_FreeSurface(surf);

	draw(texture, x * 10, y * 20);
}

void Netrom::poolEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			this->quit = true;
		}

		if (e.type == SDL_KEYDOWN) {
			this->quit = true;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			this->quit = true;
		}
	}
}

void Netrom::mainLoop() {
	while (true) {
		if (this->quit)
			break;
		SDL_RenderClear(this->ren);
		poolEvents();
		drawGlyphMatrix();
		SDL_RenderPresent(this->ren);
		SDL_Delay(100);
	}
}

void Netrom::panic(std::string msg) {
	std::cout << msg << std::endl;
	this->quit = true;
}

void Netrom::drawGlyphMatrix() {
	int i, j;
	char32_t *str = new char32_t[2];
	std::u32string source;
	std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> convert;
	std::string dest;
	for (i = 0; i < this->glyphMatrixY; i++) {
		for (j = 0; j < this->glyphMatrixX; j++) {
			char32_t c = this->glyphMatrix[i][j];
			str[0] = c;
			str[1] = '\0';
			source = str;
			dest = convert.to_bytes(source);
			drawGlyph(dest, j, i);
		}
	}
}

} /* namespace netrom */
