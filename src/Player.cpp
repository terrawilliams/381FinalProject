/*
 * Player.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: terra
 */

#include "Player.h"
#include "Engine.h"
#include "GfxMgr.h"

Player::Player()
{

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
	if(keyPressed == spawnKey)
	{

	}
}

