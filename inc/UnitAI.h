/*
 * UnitAI.h
 *
 *  Created on: Apr 28, 2018
 *      Author: nathan
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include <Aspect.h>
//#include <Command.h>
#include <deque>

class Command;

class UnitAI : Aspect
{
public:
	UnitAI(Entity381 *ent);
	~UnitAI();

	void Tick(float dt);

	void SetCommand(Command* c);
	void AddCommand(Command* c);

	std::deque<Command*> commands;
};


#endif /* INC_UNITAI_H_ */
