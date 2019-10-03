#include "Pursue.h"

Pursue::Pursue()
{
}

Pursue::~Pursue()
{
}

void Pursue::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D SteeringForce = CalculateSteeringForce(agent);
	agent->setAcceleration(SteeringForce / agent->getMass());
	agent->setVelocity(agent->getVelocity() + agent->getAcceleration() * dtime);
	agent->getVelocity().Truncate(agent->getVelocity(), agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}

Vector2D Pursue::CalculateSteeringForce(Agent* agent)
{

	Vector2D DesiredVelocity = agent->getTarget() - agent->getPosition();
	DesiredVelocity.Normalize();
	Vector2D SteeringForce;

	//ARRIVE
	Vector2D distanceToTarget = (agent->getTarget() - agent->getPosition());

	DesiredVelocity *= agent->getMaxVelocity();
	SteeringForce = (DesiredVelocity - agent->getVelocity());
	SteeringForce /= agent->getMaxVelocity();
	return SteeringForce * agent->getMaxForce();
}
