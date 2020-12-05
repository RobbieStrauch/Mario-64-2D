#pragma once
#include "Trigger.h"
#include <Box2D/Box2D.h>

class BowserTrigger : public Trigger
{
public:
	void OnTrigger() override;

	void OnEnter() override;
	void OnExit() override;

	float newSpeed;
protected:
	bool triggered = false;
};