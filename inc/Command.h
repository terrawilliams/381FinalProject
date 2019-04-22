/*
 * Command.h
 *
 *  Created on: Apr 28, 2018
 *      Author: nathan
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include <Entity381.h>

class Command
{
public:
	Command(Entity381* us) { isDone = false; ourEntity = us; };
	virtual ~Command() {};

	virtual void Tick(float dt) = 0;
	virtual void Finish() = 0;

	bool IsDone()
	{
		return isDone;
	}

protected:
	bool isDone;

	Entity381* ourEntity;
};

#endif /* INC_COMMAND_H_ */
