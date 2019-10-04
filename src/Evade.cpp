#include "Evade.h"

Evade::Evade()
{
}

Evade::~Evade()
{
}

void Evade::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D SteeringForce = CalculateSteeringForce(agent);
	agent->setAcceleration(SteeringForce / agent->getMass());
	agent->setVelocity(agent->getVelocity() + agent->getAcceleration() * dtime);
	agent->getVelocity().Truncate(agent->getVelocity(), agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}

Vector2D Evade::CalculateSteeringForce(Agent* agent)
{
	Vector2D DesiredVelocity = agent->getPosition() - agent->getTarget();
	DesiredVelocity.Normalize();
	Vector2D SteeringForce;

	Vector2D distanceToTarget = (agent->getTarget() - agent->getPosition());
	DesiredVelocity *= agent->getMaxVelocity();
	SteeringForce = (DesiredVelocity - agent->getVelocity());
	SteeringForce /= agent->getMaxVelocity();
	return SteeringForce * agent->getMaxForce();
}
