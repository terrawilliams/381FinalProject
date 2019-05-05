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
	void unitDamage(float dt);
	void baseDamage(float dt);
	void Tick(float dt);
	void restartGame();

	Engine* engine;
	Player* enemy;
	std::vector<Entity381*> units;
	Ogre::Entity* playerBase;
	Ogre::Vector3 basePosition;
	char spawnKey;
	double maxHealth, currentHealth;
	double currentResources, resourceCollectionRate;
};

#endif /* PLAYER_H_ */
