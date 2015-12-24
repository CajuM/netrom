/*
 * netrom.h
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#ifndef SRC_INCLUDE_NETROM_H_
#define SRC_INCLUDE_NETROM_H_

#include <boost/filesystem.hpp>
#include <boost/python.hpp>

namespace fs = boost::filesystem;
namespace py = boost::python;

namespace netrom {
	class Netrom;
	class Level;
	class PyScript;
	class GameObject;
}

#include "GameObject.h"
#include "Level.h"
#include "Netrom.h"
#include "PyScript.h"
#include "GameObjectList.h"


#endif /* SRC_INCLUDE_NETROM_H_ */
