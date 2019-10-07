#include "Flocking.h"

Flocking::Flocking()
{
}

Flocking::~Flocking()
{
}

void Flocking::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D FlockingForce = CalculateFlockingForce(agent);
	agent->setAcceleration(FlockingForce / agent->getMass());
	agent->setVelocity(agent->getVelocity() + agent->getAcceleration() * dtime);
	agent->getVelocity().Truncate(agent->getVelocity(), agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}

Vector2D Flocking::CalculateFlockingForce(Agent* agent)
{
	agent->Flocking_Force /= agent->getMaxVelocity();
	return agent->Flocking_Force * agent->K_flocking_force;
	//return agent->Flocking_Force;
}

