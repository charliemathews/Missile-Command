/*
	Author:			Charlie Mathews
	Modified:		November 15th, 2015
	Description: 
		This class is freaking magical. Lemme lay it down for you. 
		It uses lambda functions to make a single, all-knowing pattern
		which can be duplicated so that individual entities of any
		type can use it's glorious powers to monitor and react
		to the environment specific to any single entity.
*/

#define WIN32_LEAN_AND_MEAN
#ifndef PATTERN_H
#define PATTERN_H

#include "constants.h"
#include "entity.h"

#include <string>
#include <functional>

typedef std::function<void(Entity*)> lambda ;

class Pattern
{
private:
	typedef std::string string ;
	struct Step
	{
		string name ;
		lambda func ;
		float timeInStep, timeForStep ;
		Step(string n, float t, lambda f) : name(n), timeForStep(t), timeInStep(0), func(f) {} ;
	};
	int size ;
	int currentStep ;
	Step** steps ;

public:
	Pattern(int s) : size(s), currentStep(0)
	{
		steps = new Step* [s] ;
	};
	Pattern(const Pattern* obj) ;
	~Pattern();
	void addStep(int step_num, string step_name, float step_time, lambda step_func);
	void run(Entity* target, float frameTime);
};

#endif