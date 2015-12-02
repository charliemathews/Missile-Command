#include "patternStep.h"

PatternStep::PatternStep()
{
    active = false;                 
	timeInStep = 0;
	entity = NULL;  
	timeForStep = 0;
	action = NONE;
}

void PatternStep::initialize(Alien *e)
{
	entity = e;
}

void PatternStep::update(float frameTime)
{
	if (!active) return;

	switch (action)
	{
	case NONE:
		break;
	case ENTER:
		entity->enterStage();
		break;
	case CAMP:
		entity->camp();
		break;
	case LEAVE:
		if(entity->getX() > (-entity->getWidth()) && timeInStep > timeForStep) 
			timeForStep += frameTime+1 ;

		entity->leaveStage();
		//entity->setVelocity(D3DXVECTOR2(-1,0));
		break;
	}

	timeInStep += frameTime;
	if (timeInStep > timeForStep)
	{
		timeInStep = 0;
		active = false;
	}
}