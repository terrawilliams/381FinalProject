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
}

Player::Player(char newSpawnKey)
{
	spawnKey = newSpawnKey;
	maxHealth = 50;
	currentHealth = maxHealth;
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

void Player::CreateBase(Engine* engine, Ogre::Vector3 pos)
{
	playerBase = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(playerBase);
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

	for(int i = 0; i < units.size(); i++)
	{
		if(enemy->units.empty())
		{
			c = new MoveTo(units[i], enemy->playerBase->getParentNode()->getPosition());
		}
		else
		{
			c = new MoveTo(units[i], enemy->units[0]->position);
		}

		units[i]->GetAI()->SetCommand(c);
		units[i]->Tick(dt);
	}
}

