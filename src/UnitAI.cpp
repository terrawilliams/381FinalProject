/*
 * UnitAI.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: nathan
 */

#include <UnitAI.h>
#include <Entity381.h>
#include <Command.h>

UnitAI::UnitAI(Entity381* ent):Aspect(ent){

}

UnitAI::~UnitAI(){

}


void UnitAI::Tick(float dt){
	//A command exists
	if(!this->commands.empty())
	{
		//get oldest command
		Command* doCommand = this->commands.front();

		doCommand->Tick(dt);

		//remove the command if it completed from our last tick
		if(doCommand->IsDone())
		{
			doCommand->Finish();

			this->commands.pop_front();

			delete doCommand;//no leaks
		}
	}
}

void UnitAI::AddCommand(Command *c)
{
	this->commands.push_back(c);
}

void UnitAI::SetCommand(Command* c)
{

	this->commands.clear();
	AddCommand(c);
}
