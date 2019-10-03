#pragma once
#include "Agent.h"

class Pursue :
	public Agent::SteeringBehavior
{
public:
	Pursue();
	~Pursue();
	void applySteeringForce(Agent* agent, float dtime);
	Vector2D CalculateSteeringForce(Agent* agent);
};
