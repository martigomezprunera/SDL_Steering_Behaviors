#include "SceneSeek.h"
#include "Seek.h"
#include "Pursue.h"
#include "Wander.h"

using namespace std;

SceneSeek::SceneSeek()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Wander);
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setTargetVelocity(Vector2D(10, 10));
	agent->setVelocity(Vector2D(0, 0));
	agent->setMass(0.5);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);

	//AGENTE NUEVO
	Agent* agent1 = new Agent;
	agent1->setBehavior(new Pursue);
	agent1->setPosition(Vector2D(220, 500));
	agent1->setTarget(Vector2D(640, 360));
	agent1->setVelocity(Vector2D(1, 1));
	agent1->setMass(0.5);
	agent1->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent1);
	target = Vector2D(640, 360);
}

SceneSeek::~SceneSeek()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneSeek::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
		}
		break;
	default:
		break;
	}

	//MOVEMOS EL TARGET
	agents[0]->setTarget(target);
	agents[1]->setTarget(agents[0]->predictedPosition(agents[1], agents[0]));
	target = target + Vector2D(60, 60) * dtime;

	//UPDATE TARGET IN RANGE OF RADIUS

	//CORRECTION Y
	if (target.y >= 768)
	{
		target.y = 0;
	}
	else if(target.y <= 0)
	{
		target.y = 768;
	}

	//CORRECTION X
	if (target.x >= 1280)
	{
		target.x = 0;
	}
	else if (target.x <= 0)
	{
		target.x = 1280;
	}

	agents[0]->update(dtime,event);
	agents[1]->update(dtime, event);
}

void SceneSeek::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneSeek::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}