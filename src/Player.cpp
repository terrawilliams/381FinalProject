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
#include "Command.h"

Player::Player(Engine* newEngine)
{
	engine = newEngine;
}

Player::Player(char newSpawnKey)
{
	spawnKey = newSpawnKey;
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

