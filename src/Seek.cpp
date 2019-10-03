#include "Seek.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D SteeringForce = CalculateSteeringForce(agent);
	agent->setAcceleration(SteeringForce / agent->getMass());
	agent->setVelocity(agent->getVelocity() + agent->getAcceleration() * dtime);
	agent->getVelocity().Truncate(agent->getVelocity(), agent->getMaxVelocity());
	agent->setPosition (agent->getPosition() + agent->getVelocity() * dtime);
}

Vector2D Seek::CalculateSteeringForce(Agent *agent)
{

	Vector2D DesiredVelocity = agent->getTarget() - agent->getPosition();
	DesiredVelocity.Normalize();
	

	Vector2D distanceToTarget = (agent->getTarget() - agent->getPosition());
	if (distanceToTarget.Length() > agent->getSlowingRadius())
	{
		DesiredVelocity *= agent->getMaxVelocity();		
	}
	else
	{
		agent->setFactor(distanceToTarget.Length()/agent->getSlowingRadius());
		Vector2D SteeringForce = (DesiredVelocity - agent->getVelocity()*agent->getFactor());
	}
	Vector2D SteeringForce = (DesiredVelocity - agent->getVelocity());
	SteeringForce /= agent->getMaxVelocity();
	return SteeringForce * agent->getMaxForce();
}
