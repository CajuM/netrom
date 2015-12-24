/*
 * PyScript.h
 *
 *  Created on: Dec 23, 2015
 *      Author: mihai
 */

#ifndef SRC_PYSCRIPT_H_
#define SRC_PYSCRIPT_H_

#include "netrom.h"

#define INIT_PYNETROM_MODULE PyInit_pynetrom

extern "C" PyObject* INIT_PYNETROM_MODULE();

namespace netrom {

class PyScript {
public:
	PyScript(netrom::Netrom& gameEngine, fs::path path);

	PyThreadState* getOldstate();
	PyThreadState* getCurrentstate();

	static void del(PyScript* script);

	void bind(std::string name, py::object obj);
	void init();

	template <class T>
	static boost::python::list toPythonList(std::vector<T> vector) {
		typename std::vector<T>::iterator iter;
		boost::python::list list;
		for (iter = vector.begin(); iter != vector.end(); ++iter) {
			list.append(*iter);
		}
		return list;
	}

private:
	virtual ~PyScript();

	netrom::Netrom* gameEngine;
	fs::path path;
	py::object pyNamespace;
	PyThreadState* oldstate;
	PyThreadState* currentstate;
};

} /* namespace netrom */

#endif /* SRC_PYSCRIPT_H_ */
