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
	void setAcceleration(Vector2D NewAcceleration);
	void update(float dtime, SDL_Event *event);
	void draw();


	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	
};