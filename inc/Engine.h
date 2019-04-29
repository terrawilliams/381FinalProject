/*
 * Engine.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef ENGINE_H_
#define ENGINE_H_
#include "SoundMgr.h"

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
class UiMgr;

class Engine {
public:
	Engine();
	virtual ~Engine();

	EntityMgr *entityMgr;
	GameMgr   *gameMgr;
	GfxMgr    *gfxMgr;
	InputMgr  *inputMgr;
	OgreSND::SoundMgr *soundMgr;
	UiMgr *uiMgr;

	void Init();
	void Run();
	void TickAll(float dt);
	void Cleanup();

	bool keepRunning;
};

#endif /* ENGINE_H_ */
