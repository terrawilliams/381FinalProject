#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <Entity381.h>
#include <FlyingEntity381.h>
#include <Types381.h>
#include "Player.h"

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  //Engine *engine;

  Player *player1;
  Player *player2;

  std::vector<Entity381*> entities;
  Entity381* selectedEntity;
  FlyingEntity381* selectedFlyingEntity;
  int selectedEntityIndex;


  //Ogre::SceneManager *sceneMgr;

  void CreatePlayer1UnitOfType(EntityTypes type);
  void CreatePlayer2UnitOfType(EntityTypes type);
  void SelectNextEntity();
  void SetSelectedFlyingEntity();
  void Select(int index);
  void Destroy(Entity381* destroyedEnt);
  float SqrDistanceBetween(Ogre::Vector3 ent1Pos, Ogre::Vector3 ent2Pos);

  void LoadLevel();
  void Tick(float dt);

protected:

private:
  void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
  void CreateDDG51(Ogre::Vector3 pos);
  void CreateCarrier(Ogre::Vector3 pos);
  void CreateSpeedBoat(Ogre::Vector3 pos);
  void CreateFrigate(Ogre::Vector3 pos);
  void CreateAlien(Ogre::Vector3 pos);
  int count;

};

#endif // #ifndef __EntityMgr_h_
