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

std::string IntToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, int ident)
: soundSyscall("play '~/wavs/duck-quack2.wav'")
{

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
	UnitAI* unitAI = new UnitAI(this);
	aspects.push_back((Aspect*)unitAI);

	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;

}

Entity381::~Entity381(){

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

void Entity381::addCommand(Command* cm)
{
	for(Aspect* aspect : aspects)
	{
		aspect->addCommand(cm);
	}

}

void Entity381::setCommand(Command* cm)
{
	for(Aspect* aspect : aspects)
	{
		aspect->setCommand(cm);
	}
}

void Entity381::playSound() const
{
	pid_t forkThread = fork();
	if( forkThread < 0 )
	{
		std::cerr << "Failed to create playSound thread" << std::endl;
	} else if( forkThread == 0 )
	{
		// Child process
		system( soundSyscall.c_str() );
		exit(0);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
DDG51::DDG51(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){

	meshfilename = "ddg51.mesh";
	entityType = DDG51Type;
	this->minSpeed = 0;
	this->maxSpeed = 16.0f;//meters per second...
	this->acceleration = 5.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
	std::cout << "Created: " << this->name << std::endl;
	this->soundSyscall = "play '~/wavs/Explosion 4-SoundBible.com-1605604378.wav'";
}

DDG51::~DDG51(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Carrier::Carrier(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "cvn68.mesh";
	entityType = CarrierType;
	this->minSpeed = 0;
	this->maxSpeed = 20.0f;//meters per second...
	this->acceleration = 1.0f; // slow
	this->turnRate = 10.0f; //2 degrees per second
	this->soundSyscall = "play '~/wavs/happypika.wav' ";
}

Carrier::~Carrier(){

}
//-------------------------------------------------------------------------------------------------------------------------------

SpeedBoat::SpeedBoat(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "cigarette.mesh";
	entityType = SpeedBoatType;
	this->minSpeed = 0;
	this->maxSpeed = 30.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 30.0f; //2 degrees per second
	this->soundSyscall = "play '~/wavs/duck-quack2.wav'";
}

SpeedBoat::~SpeedBoat(){

}
//-------------------------------------------------------------------------------------------------------------------------------

Frigate::Frigate(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "sleek.mesh";
	entityType = FrigateType;
	this->minSpeed = 0;
	this->maxSpeed = 15.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 20.0f; //2 degrees per second
	this->soundSyscall = "play '~/wavs/crow-1.wav'";
}

Frigate::~Frigate(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Alien::Alien(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "alienship.mesh";
	entityType = AlienType;
	this->minSpeed = 0;
	this->maxSpeed = 50.0f;//meters per second...
	this->acceleration = 10.0f; // slow
	this->turnRate = 40.0f; //2 degrees per second
	this->soundSyscall = "play '~/wavs/laser17.wav'";
}

Alien::~Alien(){

}
//-------------------------------------------------------------------------------------------------------------------------------


