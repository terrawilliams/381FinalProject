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
	Player(Engine* newEngine);
	Player(char newSpawnKey);
	virtual ~Player();

	float SqrDistanceBetween(Ogre::Vector3 ent1Pos, Ogre::Vector3 ent2Pos);

	void CreateBase(Engine* engine, Ogre::Vector3 pos);
	void SpawnUnit(char keyPressed);
	void Tick(float dt);

	Engine* engine;
	Player* enemy;
	std::vector<Entity381*> units;
	Ogre::Entity* playerBase;
	Ogre::Vector3 basePosition;
	char spawnKey;
	int maxHealth, currentHealth;
};

#endif /* PLAYER_H_ */
