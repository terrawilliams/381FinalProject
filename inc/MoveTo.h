/*
 * MoveTo.h
 *
 *  Created on: Apr 28, 2018
 *      Author: nathan
 */

#ifndef INC_MOVETO_H_
#define INC_MOVETO_H_

#include <Command.h>
#include <Entity381.h>

class MoveTo : public Command
{
public:
	MoveTo(Entity381* ent, Ogre::Vector3 pos);
	~MoveTo();

	void Tick(float dt);
	void Finish();

private:
	Ogre::Vector3 toPos;
};


#endif /* INC_MOVETO_H_ */
