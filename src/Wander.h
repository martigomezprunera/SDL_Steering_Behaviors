#pragma once
#include "Agent.h"

class Wander :
	public Agent::SteeringBehavior
{
public:
	Wander();
	~Wander();
	void applySteeringForce(Agent* agent, float dtime);
	Vector2D CalculateSteeringForce(Agent* agent);

	//RANDOM BINOMIAL (1 to -1)
	float RandomBinomial();
};
