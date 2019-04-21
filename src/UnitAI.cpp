/*
 * UnitAI.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: imprice
 */
#include "UnitAI.h"



UnitAI::UnitAI(Entity381* ent): Aspect(ent)
{

}

UnitAI::~UnitAI()
{

}

void UnitAI::addCommand(Command* c)
{
	commands.push_back(c);
}

void UnitAI::setCommand(Command* c)
{
	commands.clear();
	commands.push_front(c);
}

void UnitAI::Tick(float dt)
{
	if( !commands.empty() )
	{
		commands.front()->Tick(dt);
		if( commands.front()->done() )
		{
			commands.pop_front();
		}
	}

}
