/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>


GameMgr::GameMgr(Engine *engine): Mgr(engine) {
	cameraNode = 0;
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){

}

void GameMgr::LoadLevel()
{
	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);



	  // A node to attach the camera to so we can move the camera node instead of the camera.
	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  cameraNode->setPosition(0, 100, 1000);
	  cameraNode->attachObject(engine->gfxMgr->mCamera);

	  engine->gfxMgr->MakeGround();
	  engine->gfxMgr->MakeSky();
	  //MakeEntities();
}

void GameMgr::Tick(float dt)
{
	if(engine->entityMgr->player1->currentHealth <= 0)
	{
		engine->gfxMgr->mSceneMgr->destroyEntity(engine->entityMgr->player1->playerBase);
		//Player2Wins();
	}

	else if(engine->entityMgr->player2->currentHealth <= 0)
	{
		engine->gfxMgr->mSceneMgr->destroyEntity(engine->entityMgr->player2->playerBase);
		//Player1Wins();
	}
}

void GameMgr::Player1Wins()
{

}

void GameMgr::Player2Wins()
{

}

void GameMgr::MakeEntities()
{
	/*Ogre::Vector3 pos = Ogre::Vector3(-1000, 0, 0);
	engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);

	pos.x = 0;
	engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);

	engine->entityMgr->SelectNextEntity(); //sets selection*/
}

