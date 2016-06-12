/*
 * Event.h
 *
 *  Created on: Jan 1, 2016
 *      Author: mihai
 */

#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

#include <string>

namespace netrom {

class Event {
public:
	Event(const std::string& eClass, const std::string& type);
	virtual ~Event();

	std::string eClass;
	std::string type;
};

class KbdEvent : public Event {
public:
	KbdEvent(const std::string& state, const std::string& keyName);
	virtual ~KbdEvent();

	std::string state;
	std::string keyName;
};

class CollisionEvent : public Event {
public:
	CollisionEvent(unsigned long long go1, unsigned long long go2);
	virtual ~CollisionEvent();

	unsigned long long go1, go2;
};

} /* namespace netrom */

#endif /* SRC_EVENT_H_ */
