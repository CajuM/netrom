/*
 * GameObject.h
 *
 *  Created on: Dec 22, 2015
 *      Author: mihai
 */

#ifndef SRC_GAMEOBJECT_H_
#define SRC_GAMEOBJECT_H_

#include <list>
#include <memory>

#include "netrom.h"
#include "Drawable.h"
#include "GlyphMat.h"
#include "Level.h"


namespace netrom {

class GameObject: public Drawable {
public:
	GameObject(netrom::Level * level,
			std::vector<netrom::GlyphMat *> icon,
			std::vector<netrom::GlyphMat *> mask);
	GameObject();
	virtual ~GameObject();

	unsigned long long getId();

	netrom::GlyphMat * draw();
	void move(int x, int y);
	netrom::GlyphMat * getMask();

	void setFrame(int frame);

	std::pair<int, int> getPos();


	void setPos(int x, int y);
	void setOrientation(int x, int y);
	std::tuple<int, int> getOrientation();

	void setNormalSpeed(double speed);

	std::tuple<int, int, int, int> getBounds();
	bool near(GameObject * go);
	bool intersects(GameObject * go);
	bool onTop(GameObject* go);
	bool isNull();

private:
	std::vector<netrom::GlyphMat *> icon;
	std::vector<netrom::GlyphMat *> mask;
	int frame;
	int x;
	int y;
	int orientationX;
	int orientationY;
	double speed;
	double maxSpeed;
	double normalSpeed;
	int maxWidth;
	int maxHeight;
	netrom::Level* level;
	unsigned long long id;
};

} /* namespace netrom */

#endif /* SRC_GAMEOBJECT_H_ */
