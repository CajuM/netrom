/*
 * pynetrom.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: mihai
 */

#include <functional>

#include <boost/python.hpp>

#include "netrom.h"
#include "Netrom.h"
#include "GameObject.h"

using namespace boost::python;

void do_nothing() {
}

BOOST_PYTHON_MODULE(pynetrom)
{
	class_<netrom::Netrom, boost::shared_ptr<netrom::Netrom>, boost::noncopyable>(
			"Netrom", py::no_init).def("__init__",
			py::make_constructor(&do_nothing));

	class_<netrom::GameObject>("GameObject");

	class_<netrom::GameObjectList>("GameObjectList")
			.def("__delitme__", &netrom::GameObjectList::__delitem__)
			.def("__getitme__", &netrom::GameObjectList::__getitem__,
					return_value_policy<reference_existing_object>()
			).def("__setitme__", &netrom::GameObjectList::__setitem__)
			.def("__len__", &netrom::GameObjectList::__len__)
			.def("append", &netrom::GameObjectList::append);
}
