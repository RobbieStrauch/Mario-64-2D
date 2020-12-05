#pragma once
#include "Trigger.h"
#include <Box2D/Box2D.h>

class HealthTrigger : public Trigger
{
public:
	void OnTrigger() override;

	void OnEnter() override;
	void OnExit() override;

	b2Vec2 movement;
	int amount;
protected:
	bool triggered = false;
};