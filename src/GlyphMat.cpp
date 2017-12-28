/*
 * GlyphMat.cpp
 *
 *  Created on: Dec 25, 2015
 *      Author: mihai
 */

#include "GlyphMat.h"
#include <cstring>

namespace netrom {

GlyphMat::GlyphMat(int x, int y, char32_t val) {
	this->x = x;
	this->y = y;
	int i, j;
	this->matrix = new char32_t*[this->y];
	for (i = 0; i < this->y; i++) {
		this->matrix[i] = new char32_t[this->x];
		for (j = 0; j < this->x; j++)
			this->matrix[i][j] = val;
	}
}

GlyphMat::GlyphMat(std::vector<std::string>& a) {
	this->y = a.size();
	if (this->y == 0) {
		this->x = 0;
		this->matrix = nullptr;
		return;
	}
	std::string d(a[0]);
	std::u32string d32 = conv::utf_to_utf<char32_t>(d);
	this->x = d32.length();
	int i, j;
	this->matrix = new char32_t*[this->y];
	for (i = 0; i < this->y; i++) {
		this->matrix[i] = new char32_t[this->x];
		std::string s(a[i]);
		std::u32string s32 = conv::utf_to_utf<char32_t>(s);
		for (j = 0; j < this->x; j++)
			this->matrix[i][j] = s32[j];
	}
}

GlyphMat::GlyphMat(char** a, int h) {
	this->y = h;
	if (this->y == 0) {
		this->x = 0;
		this->matrix = nullptr;
		return;
	}
	std::string ss(a[0]);
	std::u32string ss32 = conv::utf_to_utf<char32_t>(ss);
	this->x = ss32.length();
	this->matrix = new char32_t*[this->y];
	int i, j;
	for(i = 0; i < this->y; i++) {
		this->matrix[i] = new char32_t[this->x];
		std::string s(a[i]);
		std::u32string s32 = conv::utf_to_utf<char32_t>(s);
		for (j = 0; j < this->x; j++)
			this->matrix[i][j] = s32[j];
	}
}

GlyphMat::GlyphMat(GlyphMat* a) {
	this->x = a->x;
	this->y = a->y;

	this->matrix = new char32_t*[this->y];
	for (int i = 0; i < this->y; i++) {
		this->matrix[i] = new char32_t[this->x];
		for (int j = 0; j < this->x; j++) {
			this->matrix[i][j] = a->matrix[i][j];
		}
	}
}

GlyphMat::GlyphMat(std::vector<std::vector<char32_t>>& a) {
	this->y = a.size();
	if (this->y == 0) {
		this->x = 0;
		this->matrix = nullptr;
		return;
	}
	this->x = a[0].size();
	int i, j;
	this->matrix = new char32_t*[this->y];
	for (i = 0; i < this->y; i++) {
		this->matrix[i] = new char32_t[this->x];
		for (j = 0; j < this->x; j++)
		this->matrix[i][j] = a[i][j];
	}
}

GlyphMat::GlyphMat() {
	this->x = 0;
	this->y = 0;
	this->matrix = nullptr;
}

char32_t** GlyphMat::toC() {
	return this->matrix;
}

char32_t& GlyphMat::at(int i, int j) {
	if (i < 0 || i >= this->y)
		throw std::out_of_range("GlyphMat::at out of range i");

	if (j < 0 || j >= this->x)
		throw std::out_of_range("GlyphMat::at out of range j");

	return this->matrix[i][j];
}

GlyphMat::~GlyphMat() {
	int i;
	for (i = 0; i < this->y; i++)
		delete[] (this->matrix[i]);
	delete[] (this->matrix);
}

std::tuple<int, int> GlyphMat::getSize() {
	return std::make_pair(this->x, this->y);
}

GlyphMat * GlyphMat::copy(GlyphMat * m, int x, int y, copyMode cm) {
	int nx, ny, mx, my;
	std::tie(mx, my) = m->getSize();

	nx = std::max(mx + x, this->x);
	ny = std::max(my + y, this->y);

	GlyphMat * nm = new GlyphMat(nx, ny);
	int i, j;
	for (i = 0; i < this->y; i++)
		for (j = 0; j < this->x; j++)
			nm->at(i, j) = at(i, j);

	for (i = 0; i < my; i++)
		for (j = 0; j < mx; j++) {
			char32_t c = m->at(i, j);
			if (cm == COPY_OR) {
				if (!std::isspace(c))
					nm->at(y + i, x + j) = c;
			} else {
				nm->at(y + i, x + j) = c;
			}
		}

	return nm;
}

GlyphMat * GlyphMat::clip(size_t x, size_t y, size_t w, size_t h) {
	GlyphMat * ret = new GlyphMat(w, h);

	for (size_t i = 0; i < h; i++)
		for (size_t j = 0; j < w; j++)
			ret->at(i, j) = this->at(y + i, x + j);

	return ret;
}

GlyphMat * GlyphMat::copyMasked(GlyphMat * m, GlyphMat * gom, int x, int y) {
	int nx, ny, mx, my;
	std::tie(mx, my) = m->getSize();

	nx = std::max(mx + x, this->x);
	ny = std::max(my + y, this->y);

	GlyphMat * nm = new GlyphMat(nx, ny);
	int i, j;
	for (i = 0; i < this->y; i++)
		for (j = 0; j < this->x; j++)
			nm->at(i, j) = at(i, j);

	for (i = 0; i < my; i++)
		for (j = 0; j < mx; j++) {
			char32_t c = m->at(i, j);
			char32_t co = nm->at(y + i, x + j);
			if (!std::isgraph(gom->at(i, j)) && std::isgraph(co))
				continue;

			nm->at(y + i, x + j) = c;
		}

	return nm;
}

void GlyphMat::print() {
	int i, j;
	for (i = 0; i < this->y; i++) {
		for (j = 0; j < this->x; j++) {
			char32_t *str = new char32_t[2];
			std::u32string source;
			std::string dest;
			char32_t c = this->matrix[i][j];
			str[0] = c;
			str[1] = U'\0';
			source = str;
			delete str;
			dest = conv::utf_to_utf<char>(source);
			std::cout << dest;
		}
		std::cout << std::endl;
	}
}

} /* namespace netrom */

void steaua(std::vector<std::vector<char32_t>>* v) {
	std::cout << "steaua:" << std::endl;
	for (auto i : *v) {
		for (auto j : i) {
			std::cout << (int) j << " ";
		}

		std::cout << std::endl;
	}
}
