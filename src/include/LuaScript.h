/*
 * LuaScript.h
 *
 *  Created on: Dec 26, 2015
 *      Author: mihai
 */
#ifndef SRC_LUASCRIPT_H_
#define SRC_LUASCRIPT_H_

#include "netrom.h"
#include "Netrom.h"
#include "Level.h"
#include "Event.h"

#include <lua.hpp>

namespace netrom {

class LuaScript {
public:
	LuaScript(Level* level, fs::path script);
	virtual ~LuaScript();

	void load();

	template<typename T>
	void push(T* ptr) {
	}

	template<typename T>
	T* pop() {
	}

	template<typename T>
	void bind(std::string name, T* data) {
	}

	void event(Event* e);
	void tick();

private:
	void printErr(int ret);
	lua_State* lua;
	Level* level;
	fs::path scriptPath;
};

}
/* namespace netrom */

#endif /* SRC_LUASCRIPT_H_ */
