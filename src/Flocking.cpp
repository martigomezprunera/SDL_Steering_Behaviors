#include "Flocking.h"

Flocking::Flocking()
{
}

Flocking::~Flocking()
{
}

void Flocking::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D SteeringForce = CalculateSteeringForce(agent);
	agent->setAcceleration(SteeringForce / agent->getMass());
	agent->setVelocity(agent->getVelocity() + agent->getAcceleration() * dtime);
	agent->getVelocity().Truncate(agent->getVelocity(), agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}

Vector2D Flocking::CalculateSteeringForce(Agent* agent)
{
	agent->setVelocity(Vector2D(agent->alignmentDirection.x * agent->K_alignment_force + 
								agent->cohesionDirection.x * agent->K_cohesion_force + 
								agent->separationDirection.x * agent->K_separation_force, 
								agent->alignmentDirection.y * agent->K_alignment_force + 
								agent->cohesionDirection.y * agent->K_cohesion_force + 
								agent->separationDirection.y * agent->K_separation_force));
	//agent->setVelocity(agent->alignmentDirection.y * agent->K_alignment_force + agent->cohesionDirection.y * agent->K_cohesion_force + agent->separationDirection.y * agent->K_separation_force);
	return agent->getVelocity() * agent->getMaxForce();
}

