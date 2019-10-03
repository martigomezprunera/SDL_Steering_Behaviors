#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"


class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	Vector2D acceleration;
	Vector2D velocityTarget;

	float mass;  //change to mass
	float orientation;
	float max_force;
	float max_velocity;
	float slowingRadius;
	float ExtremeSlowingRadius;
	float factor;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Vector2D getAcceleration();
	Vector2D getVelocityTarget();

	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	float getSlowingRadius();
	float getFactor();
	float getExtremeSlowingRadius();

	void setFactor(float newFactor);
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setTargetVelocity(Vector2D NewvelocityTarget);
	void setAcceleration(Vector2D NewAcceleration);
	void setMass(float NewMass);
	void update(float dtime, SDL_Event *event);
	void draw();

	//PREDICTED TARGET
	Vector2D predictedPosition(Agent* seguidor, Agent* perseguido);

	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
};
