/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <GfxMgr.h>
#include <Engine.h>
#include <MoveTo.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	selectedEntity = 0;
	count = 0;
	selectedEntityIndex = -1;
	selectedFlyingEntity = 0;
	player1 = new Player('Z');
	player2 = new Player('M');

	player1->enemy = player2;
	player2->enemy = player1;
}

EntityMgr::~EntityMgr(){

}


void EntityMgr::SelectNextEntity(){
	if(selectedEntityIndex >= count - 1) {
		selectedEntityIndex = 0;
	} else {
		selectedEntityIndex++;
	}
	Select(selectedEntityIndex);
/*	if(selectedEntity != 0)
		selectedEntity->isSelected = false;
	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->isSelected = true;
	SetSelectedFlyingEntity();*/
}

void EntityMgr::SetSelectedFlyingEntity(){
	FlyingEntity381 *tmp = dynamic_cast<FlyingEntity381 *>(selectedEntity);
	if(tmp != 0){
		selectedFlyingEntity = tmp;
	}	else {
		selectedFlyingEntity = 0;
	}
}


void EntityMgr::Select(int i){
	if(i >= 0 && i < count){
		if(selectedEntity != 0)
			selectedEntity->isSelected = false;
		selectedEntityIndex = i;
		selectedEntity = entities[i];
		selectedEntity->isSelected = true;
		SetSelectedFlyingEntity();
	}
}

float EntityMgr::SqrDistanceBetween(Ogre::Vector3 ent1Pos, Ogre::Vector3 ent2Pos)
{
	float difX, difY, difZ;
	float difXSqr, difYSqr, difZSqr;
	float distanceSqr;

	difX = ent1Pos.x - ent2Pos.x;
	difY = ent1Pos.y - ent2Pos.y;
	difZ = ent1Pos.z - ent2Pos.z;

	difXSqr = difX * difX;
	difYSqr = difY * difY;
	difZSqr = difZ * difZ;

	distanceSqr = difXSqr + difYSqr + difZSqr;

	return distanceSqr;
}

void EntityMgr::Destroy(Entity381* destroyedEnt)
{

}


void EntityMgr::CreatePlayer1UnitOfType(EntityTypes entType){

	Entity381 * ent = 0;
	int unitCost = 0;
	Command* c;
	switch(entType){
	case BasicType:
		//CreateAlien(pos);
		unitCost = 10;
		if( player1->currentResources - unitCost > 0 )
			ent = (Entity381 *) (new Basic(engine, Ogre::Vector3(-600, 0, 0), count++));
		break;
	case RobotType:
		unitCost = 40;
		if( player1->currentResources - unitCost > 0 )
			ent = (Entity381 *) (new Robot(engine, Ogre::Vector3(-600, 0, 0), count++));
		break;
	default:
		break;
	}
	if(ent)
	{
		ent->Init();
		player1->units.push_back(ent);
		player1->currentResources -= unitCost;
		c = new MoveTo(this->engine->entityMgr->player1->units[engine->entityMgr->player1->units.size() - 1], Ogre::Vector3(600, 0, 0));
		this->engine->entityMgr->player1->units[engine->entityMgr->player1->units.size() - 1]->GetAI()->SetCommand(c);
	}
}

void EntityMgr::CreatePlayer2UnitOfType(EntityTypes entType){

	Entity381 * ent = 0;
	int unitCost = 0;
	Command* c;
	switch(entType){
	case BasicType:
		//CreateAlien(pos);
		unitCost = 10;
		if( player2->currentResources - unitCost > 0 )
			ent = (Entity381 *) (new Basic(engine, Ogre::Vector3(600, 0, 0), count++));
		break;
	case RobotType:
		unitCost = 40;
		if( player2->currentResources - unitCost > 0 )
			ent = (Entity381 *) (new Robot(engine, Ogre::Vector3(600, 0, 0), count++));
		break;
	default:
		break;
	}
	if(ent)
	{
		ent->Init();
		player2->units.push_back(ent);
		player2->currentResources -= unitCost;
		c = new MoveTo(this->engine->entityMgr->player2->units[engine->entityMgr->player2->units.size() - 1], Ogre::Vector3(-600, 0, 0));
		this->engine->entityMgr->player2->units[engine->entityMgr->player2->units.size() - 1]->GetAI()->SetCommand(c);
	}
}

void EntityMgr::LoadLevel()
{
	player1->CreateBase(engine, Ogre::Vector3(-600, 50, 0));
	player2->CreateBase(engine, Ogre::Vector3(600, 50, 0));
}

void EntityMgr::Tick(float dt)
{
	player1->Tick(dt);
	player2->Tick(dt);

	//CheckCollidingUnits();
	//CheckBaseCollision();
}

void EntityMgr::CheckCollidingUnits()
{
}

void EntityMgr::CheckBaseCollision()
{
	for(int i = 0; i < player1->units.size(); i++)
	{
		std::cout << "Base Position: (" << player2->basePosition.x << ", " << player2->basePosition.y << ", " << player2->basePosition.z << ")" << std::endl;
		std::cout << "SqrDistanceBetween " << i << " and base: " << SqrDistanceBetween(player1->units[i]->position, player2->basePosition) << std::endl;
		if(SqrDistanceBetween(player1->units[i]->position, player2->basePosition) < 100)
		{
			player2->currentHealth -= player1->units[i]->currentHealth;
			engine->gfxMgr->mSceneMgr->destroyEntity(player1->units[i]->ogreEntity);
			player1->units.erase(player1->units.begin());
		}
	}

	for(int i = 0; i < player2->units.size(); i++)
	{
		if(SqrDistanceBetween(player2->units[i]->position, player1->basePosition) < 100)
		{
			player1->currentHealth -= player2->units[i]->currentHealth;
			engine->gfxMgr->mSceneMgr->destroyEntity(player2->units[i]->ogreEntity);
			player2->units.erase(player2->units.begin());
		}
	}
}
