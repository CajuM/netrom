/*
 * Event.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: mihai
 */

#include "Event.h"

namespace netrom {

Event::Event(const std::string& eClass, const std::string& type) {
	this->eClass = eClass;
	this->type = type;
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

KbdEvent::KbdEvent(const std::string& state, const std::string& keyName) :
		Event("UI", "kbd") {
	this->state = state;
	this->keyName = keyName;
}

KbdEvent::~KbdEvent() {
	// TODO Auto-generated destructor stub
}

CollisionEvent::CollisionEvent(unsigned long long go1, unsigned long long go2) :
		Event("Game", "collision") {
	this->go1 = go1;
	this->go2 = go2;
}

CollisionEvent::~CollisionEvent() {

}

} /* namespace netrom */
