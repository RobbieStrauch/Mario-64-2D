#include "PushTrigger.h"
#include "ECS.h"

void PushTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void PushTrigger::OnEnter()
{
	Trigger::OnEnter();
	for (int i = 0; i < m_targetEntities.size(); i++)
	{
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetBody()->ApplyForceToCenter(movement, true);
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).SetHealth(ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetHealth() + amount);
	}
}

void PushTrigger::OnExit()
{
	Trigger::OnExit();
}

