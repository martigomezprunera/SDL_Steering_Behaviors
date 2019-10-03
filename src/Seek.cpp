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
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}

Vector2D Seek::CalculateSteeringForce(Agent *agent)
{

	Vector2D DesiredVelocity = agent->getTarget() - agent->getPosition();
	DesiredVelocity.Normalize();
	Vector2D SteeringForce;
	
	//ARRIVE
	Vector2D distanceToTarget = (agent->getTarget() - agent->getPosition());

	//PREDICTED
	//float T = distanceToTarget.Length() / agent->getVelocity().Length();
	float T = 3;
	Vector2D PredictedTarget = (agent->getTarget() + agent->getVelocityTarget()) * T;

	if (distanceToTarget.Length() > agent->getSlowingRadius())
	{
		DesiredVelocity *= agent->getMaxVelocity();	
		SteeringForce = (DesiredVelocity - agent->getVelocity());
	}
	else
	{
		if (distanceToTarget.Length() <= agent->getExtremeSlowingRadius())
		{
			agent->setFactor(distanceToTarget.Length() / agent->getExtremeSlowingRadius() + 5);
		}
		else
		{
			agent->setFactor(distanceToTarget.Length() / agent->getSlowingRadius());
		}
		SteeringForce = (DesiredVelocity - agent->getVelocity()*agent->getFactor());
	}

	SteeringForce /= agent->getMaxVelocity();
	return SteeringForce * agent->getMaxForce();
}
