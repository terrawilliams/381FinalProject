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

void Player::unitDamage(float dt)
{
	for(Entity381* myUnit : units)
	{
//		std::cout <<
		if(enemy->units.size() > 0 and SqrDistanceBetween(myUnit->position, enemy->units[0]->position) < 1000)
		{
			enemy->units[0]->currentHealth -= myUnit->dps * dt;
//				if(units[i]->currentHealth > ->currentHealth)
//				{
//					player1->units[i]->currentHealth -= player2->units[j]->currentHealth;
//					engine->gfxMgr->mSceneMgr->destroyEntity(player2->units[0]->ogreEntity);
//					player2->units.erase(player2->units.begin());
//				}
//				else if(player1->units[i]->currentHealth < player2->units[j]->currentHealth)
//				{
//					player2->units[j]->currentHealth -= player1->units[i]->currentHealth;
//					engine->gfxMgr->mSceneMgr->destroyEntity(player1->units[0]->ogreEntity);
//					player1->units.erase(player1->units.begin());
//				}
//				else
//				{
//					engine->gfxMgr->mSceneMgr->destroyEntity(player1->units[0]->ogreEntity);
//					engine->gfxMgr->mSceneMgr->destroyEntity(player2->units[0]->ogreEntity);
//					player1->units.erase(player1->units.begin());
//					player2->units.erase(player2->units.begin());
//				}
		}
	}

	// Delete dead unit
	if(enemy->units.size() > 0 and enemy->units[0]->currentHealth < 0)
	{
		//engine->gfxMgr->mSceneMgr->destroyEntity(enemy->units[0]->ogreEntity);
		enemy->units[0]->position = Ogre::Vector3(0, -500, 0);
		enemy->units[0]->Tick(dt);
		enemy->units.erase(enemy->units.begin());
	}

}

void Player::baseDamage(float dt)
{
	for(int i = 0; i < enemy->units.size(); i++)
	{
		if(units.size() == 0 and SqrDistanceBetween(enemy->units[i]->position, basePosition) < 1000)
		{
			currentHealth -= enemy->units[i]->dps * dt;
		}
	}
	if(currentHealth < 0)
	{
		// Base has died!
	}

}

void Player::Tick(float dt)
{
	Command* c;

	unitDamage(dt);
	baseDamage(dt);

	for(int i = 0; i < units.size(); i++)
	{
		c = nullptr;
		if(enemy->units.empty())
		{
			c = new MoveTo(units[i], enemy->basePosition);
		}
		else if ( SqrDistanceBetween(units[i]->position, enemy->units[0]->position) > 1000)
		{
			c = new MoveTo(units[i], enemy->units[0]->position);
		}
		else
		{
			units[i]->GetAI()->commands.clear();
			units[i]->desiredSpeed = 0;
		}
		if(c)
			units[i]->GetAI()->SetCommand(c);
		units[i]->Tick(dt);
	}
	currentResources += dt * resourceCollectionRate;
}

