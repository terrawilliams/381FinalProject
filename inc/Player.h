/*
 * Player.h
 *
 *  Created on: Apr 28, 2019
 *      Author: terra
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <Entity381.h>

class Player {
public:
	Player();
	virtual ~Player();

	void CreateBase(Engine* engine);
	void SpawnUnit(char keyPressed);

	std::vector<Entity381*> units;
	Ogre::Entity* playerBase;
};

#endif /* PLAYER_H_ */
