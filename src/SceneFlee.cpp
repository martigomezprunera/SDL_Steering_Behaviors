#include "SceneFlee.h"
#include "Flee.h"
#include "Evade.h"
#include "Seek.h"
#include "Pursue.h"

using namespace std;

SceneFlee::SceneFlee()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Pursue);
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.5);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent* agent1 = new Agent;
	agent1->setBehavior(new Evade);
	agent1->setPosition(Vector2D(400, 360));
	agent1->setTarget(Vector2D(640, 360));
	agent1->setMass(0.5);
	agent1->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent1);
	target = Vector2D(640, 360);
}

SceneFlee::~SceneFlee()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlee::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
			agents[1]->setTarget(agents[1]->predictedPositionEvade(agents[1], agents[0]));
		}
		break;
	default:
		break;
	}
	agents[0]->update(dtime,event);
	agents[1]->update(dtime, event);
}

void SceneFlee::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneFlee::getTitle()
{
	return "SDL Steering Behaviors :: Flee Demo";
}