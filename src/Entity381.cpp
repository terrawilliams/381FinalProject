/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <GfxMgr.h>

#include<Entity381.h>
#include<Physics2D.h>
#include<UnitAI.h>


unsigned int Entity381::nextId = 0;

std::string IntToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, int ident){

	this->engine = engine;

	entityType = None;
	meshfilename = std::string();
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = ident;
	isSelected = false;

	name = "Entity381";//meshfname + IntToString(identity);
/*
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);*/
	sceneNode = 0;
	ogreEntity = 0;

	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	ai = new UnitAI(this);
	aspects.push_back((Aspect*)ai);

	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;
	this->soundFile = "Boat-Sound.wav";
	this->auioId = 0;
	this->didSelectSoundPlay = false;
	this->playSound = false;
	this->entityId = Entity381::nextId++;
	maxHealth = currentHealth = dps = 0;

}

Entity381::~Entity381(){

}

UnitAI* Entity381::GetAI()
{
	return ai;
}

void Entity381::Init(){

	name = meshfilename + IntToString(identity);
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
Basic::Basic(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "penguin.mesh";
	entityType = BasicType;
	this->minSpeed = 0;
	this->maxSpeed = 50.0f;//meters per second...
	this->acceleration = 500.0f; // slow
	this->turnRate = 400.0f; //2 degrees per second
	maxHealth = 10;
	currentHealth = maxHealth;
	dps = 1;
}

Basic::~Basic(){

}
//-------------------------------------------------------------------------------------------------------------------------------
Robot::Robot(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "robot.mesh";
	entityType = RobotType;
	this->minSpeed = 0;
	this->maxSpeed = 50.0f;//meters per second...
	this->acceleration = 500.0f; // slow
	this->turnRate = 400.0f; //2 degrees per second
	maxHealth = 40;
	currentHealth = maxHealth;
	dps = 1;
}

Robot::~Robot(){

}
//-------------------------------------------------------------------------------------------------------------------------------
Ninja::Ninja(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "ninja.mesh";
	entityType = NinjaType;
	this->minSpeed = 0;
	this->maxSpeed = 50.0f;//meters per second...
	this->acceleration = 500.0f; // slow
	this->turnRate = 400.0f; //2 degrees per second
	maxHealth = 10;
	currentHealth = maxHealth;
	dps = 1;
}

Ninja::~Ninja(){

}
