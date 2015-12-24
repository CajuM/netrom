/*
 * GameObjectList.h
 *
 *  Created on: Dec 24, 2015
 *      Author: mihai
 */

#ifndef SRC_GAMEOBJECTLIST_H_
#define SRC_GAMEOBJECTLIST_H_

#include "netrom.h"

namespace netrom {

class GameObjectList {
public:
	GameObjectList(std::vector<GameObject>& gameObjects);
	GameObjectList();
	virtual ~GameObjectList();

	void __delitem__(size_t key);
	GameObject& __getitem__(size_t key);
	void __setitem__(size_t key, GameObject& gameObject);
	size_t __len__();
	void append(GameObject gameObject);

	operator py::object();

private:
	std::vector<GameObject>* gameObjects;
	bool distructable;
};

} /* namespace netrom */

#endif /* SRC_GAMEOBJECTLIST_H_ */
