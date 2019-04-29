/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <GfxMgr.h>
#include <Engine.h>

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

	Entity381 * ent;
	switch(entType){
	case BasicType:
		//CreateAlien(pos);
		ent = (Entity381 *) (new Basic(engine, Ogre::Vector3(-600, 0, 0), count++));
		break;
	default:
		break;
	}
	ent->Init();
	player1->units.push_back(ent);
}

void EntityMgr::CreatePlayer2UnitOfType(EntityTypes entType){

	Entity381 * ent;
	switch(entType){
	case BasicType:
		//CreateAlien(pos);
		ent = (Entity381 *) (new Basic(engine, Ogre::Vector3(600, 0, 0), count++));
		break;
	default:
		break;
	}
	ent->Init();
	player2->units.push_back(ent);
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

	for(int i = 0; i < player1->units.size(); i++)
	{
		for(int j = 0; j < player2->units.size(); j++)
		{
			if(SqrDistanceBetween(player1->units[i]->position, player2->units[j]->position) < 4)
			{
				if(player1->units[i]->currentHealth > player2->units[j]->currentHealth)
				{
					player1->units[i]->currentHealth -= player2->units[j]->currentHealth;
					engine->gfxMgr->mSceneMgr->destroyEntity(player2->units[0]->ogreEntity);
					player2->units.erase(player2->units.begin());
				}
				else if(player1->units[i]->currentHealth < player2->units[j]->currentHealth)
				{
					player2->units[j]->currentHealth -= player1->units[i]->currentHealth;
					engine->gfxMgr->mSceneMgr->destroyEntity(player1->units[0]->ogreEntity);
					player1->units.erase(player1->units.begin());
				}
				else
				{
					engine->gfxMgr->mSceneMgr->destroyEntity(player1->units[0]->ogreEntity);
					engine->gfxMgr->mSceneMgr->destroyEntity(player2->units[0]->ogreEntity);
					player1->units.erase(player1->units.begin());
					player2->units.erase(player2->units.begin());
				}
			}
		}
	}
}
