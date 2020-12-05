#include "HealthTrigger.h"
#include "ECS.h"

void HealthTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void HealthTrigger::OnEnter()
{
	Trigger::OnEnter();
	for (int i = 0; i < m_targetEntities.size(); i++)
	{
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).SetHealth(ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetHealth() + amount);
	}
}

void HealthTrigger::OnExit()
{
	Trigger::OnExit();
}

