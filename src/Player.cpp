/*
 * Player.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: terra
 */

#include "Player.h"
#include "Engine.h"
#include "GfxMgr.h"
#include "EntityMgr.h"
#include "Intercept.h"
#include "MoveTo.h"

Player::Player(Engine* newEngine)
{
	engine = newEngine;
	maxHealth = 50;
	currentHealth = maxHealth;
	currentResources = 0;
	resourceCollectionRate = 2;
}

Player::Player(char newSpawnKey)
{
	spawnKey = newSpawnKey;
	maxHealth = 50;
	currentHealth = maxHealth;
	currentResources = 0;
	resourceCollectionRate = 2;
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

float Player::SqrDistanceBetween(Ogre::Vector3 ent1Pos, Ogre::Vector3 ent2Pos)

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

void Player::CreateBase(Engine* engine, Ogre::Vector3 pos)
{
	playerBase = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(playerBase);

	basePosition = pos;
	basePosition.y = 0;
}

void Player::SpawnUnit(char keyPressed)
{
	Command* c;

	if(keyPressed == spawnKey)
	{
		/*engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, Ogre::Vector3(-600, 0, 0));
		engine->entityMgr->SelectNextEntity();
		c = new MoveTo(unit, enemy->playerBase->mParentNode->getPosition());
		this->engine->entityMgr->selectedEntity->GetAI()->SetCommand(c);*/
	}
}

void Player::Tick(float dt)
{
	Command* c;

	for(int i = 0; i < enemy->units.size(); i++)
	{
		if(SqrDistanceBetween(enemy->units[i]->position, basePosition) < 36)
		{
			std::cout << "Enemy collided with base///////////////////////////////\n\n" << std::endl;
			currentHealth -= enemy->units[i]->currentHealth;
			engine->gfxMgr->mSceneMgr->destroyEntity(enemy->units[i]->ogreEntity);
			enemy->units.erase(enemy->units.begin());
		}
	}

	for(int i = 0; i < units.size(); i++)
	{
		if(enemy->units.empty())
		{
			c = new MoveTo(units[i], enemy->basePosition);
		}
		else
		{
			c = new MoveTo(units[i], enemy->units[0]->position);
		}

		units[i]->GetAI()->SetCommand(c);
		units[i]->Tick(dt);
	}
	currentResources += dt * resourceCollectionRate;
}

