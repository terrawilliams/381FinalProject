/*
 * Command.h
 *
 *  Created on: Apr 7, 2019
 *      Author: imprice
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include <Entity381.h>
#include <OgreVector3.h>
#include <cmath>

const double PI = 3.14159265;


class Command {

public:
	Command(Entity381* ent, COMMAND_TYPE ct);
	virtual ~Command();

	virtual void init();
	virtual void Tick(float dt);
	virtual bool done();

	Entity381* entity;
	COMMAND_TYPE commandType;

};

class MoveTo: public Command {

public:
	MoveTo(Entity381* ent, Ogre::Vector3 location);
	~MoveTo();

	void init();
	void Tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;
	bool decelerating;

};

class Intercept: public Command
{
public:
	Intercept(Entity381* ent, Entity381* target);
	~Intercept();

	void init();
	void Tick(float dt);
	bool done();

	Entity381* target;
};

#endif /* INC_COMMAND_H_ */
