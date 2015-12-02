/*
	Author:			Charlie Mathews
	Modified:		November 15th, 2015
	Description:	(see header)
*/

#include "pattern.h"

//copy constructor for duplicating the pattern
Pattern::Pattern(const Pattern* obj)
{
	size = obj->size ;
	currentStep = obj->currentStep ;

	steps = new Step* [size] ;

	for(int i = 0; i < size; ++i)
	{
		Step* s = obj->steps[i] ;
		steps[i] = new Step(s->name, s->timeForStep, s->func) ;
	}
}

Pattern::~Pattern()
{
	for(int i = 0; i < size; ++i) delete steps[i] ;
	delete [] steps ;
}
	
void Pattern::addStep(int step_num, string step_name, float step_time, lambda step_func)
{
	steps[step_num] = new Step(step_name, step_time, step_func);
}
	
void Pattern::run(Entity* target, float frameTime)
{
	if(currentStep >= size) return ;
	Step* s = steps[currentStep] ;
	s->func(target) ;
	s->timeInStep += frameTime ;
	if(s->timeInStep >= s->timeForStep) currentStep++ ;
}
