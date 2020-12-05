#include "StarTrigger.h"
#include "ECS.h"

void StarTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void StarTrigger::OnEnter()
{
	Trigger::OnEnter();
	for (int i = 0; i < m_targetEntities.size(); i++)
	{
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).SetStar(ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetStar() + amount);
	}
}

void StarTrigger::OnExit()
{
	Trigger::OnExit();
}
