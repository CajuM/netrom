/*
 * GlyphMat.h
 *
 *  Created on: Dec 25, 2015
 *      Author: mihai
 */

#ifndef SRC_GLYPHMAT_H_
#define SRC_GLYPHMAT_H_

#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include <memory>

#include "netrom.h"

namespace netrom {

class GlyphMat {
public:
	GlyphMat(int x, int y, char32_t val = '\0');
	GlyphMat(std::vector<std::string>& a);
	GlyphMat(std::vector<std::vector<char32_t>>& a);
	GlyphMat(char** a, int h);
	GlyphMat();
	GlyphMat(const GlyphMat& m);
	virtual ~GlyphMat();

	enum copyMode {
		COPY_OR,
		COPY_FIFS
	};

	char32_t** toC();
	char32_t& at(int i, int j);
	std::tuple<int, int> getSize();
	GlyphMat copy(GlyphMat& m, int x, int y, copyMode cm);
	GlyphMat copyMasked(GlyphMat& m, GlyphMat& gom, int x, int y);
	GlyphMat clip(int x, int y, int w, int h);
	void print();

	GlyphMat& operator=(const GlyphMat& m);

private:
	char32_t** matrix;
	int x, y;
};

} /* namespace netrom */

void steaua(std::vector<std::vector<char32_t>>* v);

#endif /* SRC_GLYPHMAT_H_ */
