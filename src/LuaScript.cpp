/*
 * LuaScript.cpp
 *
 *  Created on: Dec 26, 2015
 *      Author: mihai
 */

#include "LuaScript.h"
#include "MsgBox.h"
#include "Scene.h"
#include "GameObject.h"

namespace netrom {

LuaScript::LuaScript(Level* level, fs::path scriptPath) {
	this->level = level;
	this->scriptPath = scriptPath;
	this->lua = luaL_newstate();
	luaL_openlibs(this->lua);

	if (this->level->getGameEngine()->debugEnabled()) {
		luaL_dostring(this->lua,
				"jit = require('jit') ; jit.off() ; print('Jit disabled')");
	}

	std::string luaPath = (this->level->getGameEngine()->getRes() / "levels"
			/ "gamelib" / "?.lua").native();

	lua_getglobal(this->lua, "package");
	lua_pushstring(this->lua, luaPath.c_str());
	lua_setfield(this->lua, -2, "path");

	lua_pushlightuserdata(this->lua, level);
	lua_setglobal(this->lua, "currentLevel");

	lua_pushlightuserdata(this->lua, level->getGameEngine());
	lua_setglobal(this->lua, "gameEngine");
}

void LuaScript::printErr(int ret) {
	if (ret == 0) {
		return;
	}
    lua_getglobal(this->lua, "debug");
    lua_getfield(this->lua, -1, "traceback");
    lua_remove(this->lua, -2);
    lua_call(this->lua, 0, 0);
	std::cout << lua_tostring(this->lua, -1) << std::endl;
}

void LuaScript::load() {
	luaL_loadfile(this->lua, this->scriptPath.native().c_str());
	int ret = lua_pcall(this->lua, 0, LUA_MULTRET, 0);
	printErr(ret);
}

LuaScript::~LuaScript() {
	lua_close(this->lua);
}

void LuaScript::tick() {
	lua_getglobal(this->lua, "tick");
	int ret = lua_pcall(this->lua, 0, 0, 0);
	printErr(ret);
}

void LuaScript::event(Event * e) {
	lua_getglobal(this->lua, "queueEvent");

	lua_newtable(this->lua);

	lua_pushstring(this->lua, "eClass");
	lua_pushstring(this->lua, e->eClass.c_str());
	lua_settable(this->lua, -3);

	lua_pushstring(this->lua, "type");
	lua_pushstring(this->lua, e->type.c_str());
	lua_settable(this->lua, -3);

	lua_pushstring(this->lua, "val");
	lua_newtable(this->lua);
	if (e->eClass == "UI" && e->type == "kbd") {
		KbdEvent * ev = (KbdEvent *) e;

		lua_pushstring(this->lua, "state");
		lua_pushstring(this->lua, ev->state.c_str());
		lua_settable(this->lua, -3);

		lua_pushstring(this->lua, "keyName");
		lua_pushstring(this->lua, ev->keyName.c_str());
		lua_settable(this->lua, -3);
	}
	if (e->eClass == "Game" && e->type == "collision") {
		CollisionEvent * ev = (CollisionEvent *) e;

		lua_pushstring(this->lua, "go1");
		lua_pushnumber(this->lua, ev->go1);
		lua_settable(this->lua, -3);

		lua_pushstring(this->lua, "go2");
		lua_pushnumber(this->lua, ev->go2);
		lua_settable(this->lua, -3);
	}
	lua_settable(this->lua, -3);

	int ret = lua_pcall(this->lua, 1, 0, 0);
	printErr(ret);
	delete e;
}

} /* namespace netrom */
