#pragma once
#include "Trigger.h"
#include <Box2D/Box2D.h>

class StarTrigger : public Trigger
{
public:
	void OnTrigger() override;

	void OnEnter() override;
	void OnExit() override;

	int amount = 0;
protected:
	bool triggered = false;
};


