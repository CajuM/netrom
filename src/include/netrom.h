/*
 * netrom.h
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#ifndef SRC_INCLUDE_NETROM_H_
#define SRC_INCLUDE_NETROM_H_

#include <boost/filesystem.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/shared_ptr.hpp>

namespace fs = boost::filesystem;
namespace conv = boost::locale::conv;

namespace netrom {
	class Netrom;
	class Level;
	class GameObject;
	class UIElement;
	class MsgBox;
	class GlyphMat;
	class Drawable;
	class LuaScript;

	template<typename T1, typename T2>
	std::list<T1 *> ptrListConv(std::list<T2 *> p) {
		std::list<T1 *> nl;
		for (auto i : p)
			nl.push_back(i);
		return nl;
	}
}

#endif /* SRC_INCLUDE_NETROM_H_ */
