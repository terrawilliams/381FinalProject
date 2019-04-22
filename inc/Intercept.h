/*
 * MoveTo.h
 *
 *  Created on: Apr 28, 2018
 *      Author: nathan
 */

#ifndef INC_INTERCEPT_H_
#define INC_INTERCEPT_H_

#include <Command.h>
#include <Entity381.h>

class Intercept : public Command
{
public:
	Intercept(Entity381* ent, Entity381* tgt);
	~Intercept();

	void Tick(float dt);
	void Finish();

private:
	Entity381* target;
};


#endif /* INC_MOVETO_H_ */
