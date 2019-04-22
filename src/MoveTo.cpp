/*
 * MoveTo.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: nathan
 */

#include <MoveTo.h>
#include <cmath>
#include <Utils.h>

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 pos) : Command(ent)
{
	this->toPos = pos;
}

MoveTo::~MoveTo()
{
}

void MoveTo::Tick(float dt)
{
	//Calculate heading
	Ogre::Vector3 diff = toPos - this->ourEntity->position;
	this->ourEntity->desiredHeading = atan2(diff.z, diff.x) * (180.0/3.141592);
	this->ourEntity->desiredHeading = FixAngle(this->ourEntity->desiredHeading);

	//Calculate velocity
	this->ourEntity->desiredSpeed = this->ourEntity->maxSpeed;

	std::cout << "tick move" << std::endl;

	if(this->ourEntity->position.distance(toPos) < 10)
	{
		this->isDone = true;
	}
}

void MoveTo::Finish()
{
	this->ourEntity->desiredSpeed = 0;
}

