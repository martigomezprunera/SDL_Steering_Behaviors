#pragma once
#include "Agent.h"

class Flocking :
	public Agent::SteeringBehavior
{
public:
	Flocking();
	~Flocking();
	void applySteeringForce(Agent* agent, float dtime);
	Vector2D CalculateSteeringForce(Agent* agent);
};
