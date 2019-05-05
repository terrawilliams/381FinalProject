/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void Tick(float dt);
	void LoadLevel();

	void MakeGround();
	void MakeSky();
	void MakeEntities();

	void Player1Wins();
	void Player2Wins();

	Ogre::SceneNode *cameraNode;
	int gameStarted; // Made it an int in case we need a third state for game ended or something. Currently 0 is not started, 1 is started.

};

#endif /* GAMEMGR_H_ */
