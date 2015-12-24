/*
 * PyScript.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: mihai
 */

#include <iostream>

#include "PyScript.h"

namespace netrom {

PyScript::PyScript(netrom::Netrom& gameEngine, fs::path path) {
	this->gameEngine = &gameEngine;
	this->path = path;
	try {
		this->oldstate = PyEval_SaveThread();
		this->currentstate = Py_NewInterpreter();
		py::object main_module = py::import("__main__");
		py::object pynetrom_module = py::import("pynetrom");
		this->pyNamespace = py::extract<py::dict>(main_module.attr("__dict__"));
		this->pyNamespace["pynetrom"] = pynetrom_module;
	} catch (...) {
		PyErr_PrintEx(0);
	}
}

PyScript::~PyScript() {
}

void PyScript::del(PyScript* script) {
	PyThreadState* oldstate = script->getOldstate();
	PyThreadState* currentstate = script->getCurrentstate();
	delete script;
	Py_EndInterpreter(currentstate);
	PyEval_RestoreThread(oldstate);
}

void PyScript::init() {
	try {
		py::exec_file(path.native().c_str(), this->pyNamespace,
				this->pyNamespace);
	} catch (...) {
		PyErr_PrintEx(0);
	}
}

PyThreadState* PyScript::getOldstate() {
	return this->oldstate;
}

PyThreadState* PyScript::getCurrentstate() {
	return this->currentstate;
}

void PyScript::bind(std::string name, py::object obj) {
	this->pyNamespace[name] = obj;
}

} /* namespace netrom */
