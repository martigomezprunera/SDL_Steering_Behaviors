#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneSeek :
	public Scene
{
public:
	SceneSeek();
	~SceneSeek();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;

	Vector2D targetVelocity;
	float targetAngle;
	float counterFrames;
	int velocity;
	Vector2D targetCircle;
	Vector2D targetRandom;

	int firstTime;

};

