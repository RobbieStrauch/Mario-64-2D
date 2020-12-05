#include "BowserTrigger.h"
#include "ECS.h"

void BowserTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void BowserTrigger::OnEnter()
{
	Trigger::OnEnter();
	for (int i = 0; i < m_targetEntities.size(); i++)
	{
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).speed = newSpeed;
	}
}

void BowserTrigger::OnExit()
{
	Trigger::OnExit();
}

