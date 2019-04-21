/*
 * Command.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: imprice
 */
#include "Command.h"

Command::Command(Entity381* ent, COMMAND_TYPE ct): entity(ent), commandType(ct)
{

}

Command::~Command()
{

}

bool Command::done()
{
	return false;
}

void Command::init()
{

}

void Command::Tick(float dt)
{

}


//////////////////
/* MoveTo stuff */
//////////////////

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location): Command(ent, MOVETO), targetLocation(location), decelerating(false)
{
	MOVE_DISTANCE_THRESHOLD = 0;
}

MoveTo::~MoveTo()
{

}

bool MoveTo::done()
{
	if( decelerating && entity->speed == 0 )
	{
		entity->desiredSpeed = 0;
		decelerating = false;
		return true;
	} else
	{
		return false;
	}
}

void MoveTo::init()
{
}

void MoveTo::Tick(float dt)
{
	float speed = entity->maxSpeed;
	static float avgDt = dt;
	static int numTimesRan = 1;
	avgDt = avgDt*numTimesRan++ + dt;
	avgDt /= numTimesRan;
	Ogre::Vector3 differencePosition = entity->position - targetLocation;
	float distanceSq = differencePosition.y * differencePosition.y + differencePosition.z * differencePosition.z;
	float decelerationDistance = (entity->speed * entity->speed)/(2 * entity->acceleration * avgDt);
	if( decelerating || distanceSq < decelerationDistance )
	{
		decelerating = true;
		speed = 0;
	}
	// Do some speed stuff to slow down
	entity->desiredHeading = 360 - atan2( (entity->position.z - targetLocation.z), -(entity->position.x - targetLocation.x)) * 180/PI;
	entity->desiredSpeed = speed;
}

///////////////////
/*Intercept Stuff*/
///////////////////

Intercept::Intercept(Entity381* ent, Entity381* target): Command(ent, INTERCEPT), target(target)
{

}
Intercept::~Intercept()
{

}

void Intercept::init()
{

}
void Intercept::Tick(float dt)
{
	//calculate desired position
	Ogre::Vector3 interceptionPt = target->position + (target->velocity * dt);

	//update speed
	float speed = entity->maxSpeed;
	static float avgDt = dt;
	static int numTimesRan = 1;

	avgDt = avgDt*numTimesRan++ + dt;
	avgDt /= numTimesRan;

	Ogre::Vector3 differencePosition = entity->position - target->position;
	float distanceSq = differencePosition.y * differencePosition.y + differencePosition.z * differencePosition.z;
	float decelerationDistance = (entity->speed * entity->speed)/(2 * entity->acceleration * avgDt);

	if(distanceSq < decelerationDistance)
		speed = target->speed;

	entity->desiredSpeed = speed;

	//update rotation
	entity->desiredHeading = 360 - atan2( (entity->position.z - interceptionPt.z), -(entity->position.x - interceptionPt.x)) * 180/PI;
}
bool Intercept::done()
{
	return false;
}
