#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Types381.h>

#include <Engine.h>
#include <UnitAI.h>


class Entity381
{
public:
  Entity381(Engine *engine, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  Engine *engine;

  //static data
  int identity;
  std::string name;
  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;
  float acceleration, turnRate;
  float minSpeed, maxSpeed;

  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  bool isSelected;
  float desiredHeading, desiredSpeed;
  float heading, speed;
  float maxHealth, currentHealth, dps;

  EntityTypes entityType;

  std::vector<Aspect* > aspects;

	//sound
	bool didSelectSoundPlay;
	std::string soundFile;
	bool playSound;
	unsigned int auioId;

	unsigned int entityId;

  void Init();

  void Tick(float dt);

  UnitAI* GetAI();

private:
  UnitAI* ai;
  static unsigned int nextId;

protected:


};


class Basic: public Entity381 {
public:
	Basic(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Basic();

};


#endif // #ifndef __Entity381_h_
