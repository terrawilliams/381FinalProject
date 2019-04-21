/*
 * UnitAI.h
 *
 *  Created on: Apr 7, 2019
 *      Author: imprice
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_
#include <Aspect.h>
#include <Command.h>


class UnitAI : Aspect
{
public:
	UnitAI(Entity381* ent);
	~UnitAI();

	void setCommand(Command *c);
	void addCommand(Command *c);

	void Tick(float dt);

	std::list<Command*> commands;
};


#endif /* INC_UNITAI_H_ */
