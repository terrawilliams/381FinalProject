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

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

void Player::CreateBase(Engine* engine)
{
	playerBase = engine->gfxMgr->mSceneMgr->createEntity("robot.mesh");
	Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-600, 0, 0));
	sceneNode->attachObject(playerBase);
}

void Player::SpawnUnit(char keyPressed)
{
	if(keyPressed == 'Z')
	{

	}
	else if(keyPressed == 'X')
	{

	}
	else if(keyPressed == 'C')
	{

	}
}

