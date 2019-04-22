/*
 * MoveTo.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: nathan
 */

#include <Intercept.h>
#include <cmath>
#include <Utils.h>

Intercept::Intercept(Entity381* ent, Entity381* tgt) : Command(ent)
{
	this->target = tgt;
}

Intercept::~Intercept()
{
}

void Intercept::Tick(float dt)
{
	//Calculate heading
	Ogre::Vector3 rel = this->target->velocity - this->ourEntity->velocity;

	float dist = this->ourEntity->position.distance(this->target->position);
	float t = dist / rel.length();

	Ogre::Vector3 diff = (this->target->position + this->target->velocity * t) - this->ourEntity->position;

	this->ourEntity->desiredHeading = atan2(diff.z, diff.x) * (180.0/3.141592);
	this->ourEntity->desiredHeading = FixAngle(this->ourEntity->desiredHeading);

	//Calculate velocity
	this->ourEntity->desiredSpeed = this->ourEntity->maxSpeed;

	if(dist < 10)
	{
		this->isDone = true;
	}
}

void Intercept::Finish()
{
	this->ourEntity->desiredSpeed = 0;
}

