#include "Wander.h"

Wander::Wander()
{
}

Wander::~Wander()
{
}

void Wander::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D SteeringForce = CalculateSteeringForce(agent);
	agent->setAcceleration(SteeringForce / agent->getMass());
	agent->setVelocity(agent->getVelocity() + agent->getAcceleration() * dtime);
	agent->getVelocity().Truncate(agent->getVelocity(), agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}

Vector2D Wander::CalculateSteeringForce(Agent* agent)
{
	//CONSTANTS WANDER
	// Wander Angle
	float WanderAngle = 0;
	// Target Angle
	float TargetAngle;
	// Maximum Change of Angle in one frame
	float WanderMaxAngleChange = 35;
	// Distance from Agent to Wander Circle Center
	float WanderOffset = 1;
	// Radius of Wander Circle
	float WanderRadius = 100;
	//Circle center
	Vector2D CircleCenter;

	Vector2D DesiredVelocity = agent->getTarget() - agent->getPosition();
	DesiredVelocity.Normalize();
	Vector2D SteeringForce;

	//ARRIVE
	Vector2D distanceToTarget = (agent->getTarget() - agent->getPosition());

	//PREDICTED
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
		SteeringForce = (DesiredVelocity - agent->getVelocity() * agent->getFactor());
	}

	SteeringForce /= agent->getMaxVelocity();
	return SteeringForce * agent->getMaxForce();
}

float Wander::RandomBinomial()
{ 
	return ((rand() / RAND_MAX)) - (rand() / (RAND_MAX));
}
