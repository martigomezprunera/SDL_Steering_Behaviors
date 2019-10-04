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

	//TARGET VELOCITY
	targetVelocity = Vector2D(1, 1);
	counterFrames = 0;
	velocity = 60;

	//TARGET CIRCLE
	targetCircle = Vector2D(640, 360) + Vector2D(60, 60);

	//TARGET RANDOM
	targetRandom = targetCircle + Vector2D(30, 0);

	//FIRSTFRAME TARGET
	firstTime = 0;
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

	targetAngle = rand() % 15;
	target = target + targetVelocity * velocity * dtime;

	//ACTUALIZAMOS EL CIRCULO DE DELANTE DEL TARGET
	targetCircle.x = target.x + (targetVelocity.x * 60);
	targetCircle.y = target.y + (targetVelocity.y * 60);

	//ACTUALIZAMOS TARGETRANDOM CIRCULO
	if (firstTime == 0)
	{
		targetRandom.x = target.x + (targetVelocity.x * (60 + 25));
		targetRandom.y = target.y + (targetVelocity.y * (60 + 25));
	}
	counterFrames++;

	if (counterFrames == 1000)
	{
		counterFrames = 0;
		targetRandom.x = targetCircle.x + 40 * cos(targetAngle);
		targetRandom.y = targetCircle.y + 40 * sin(targetAngle);
		firstTime = 1;

		targetVelocity = targetRandom - target;
		targetVelocity.Normalize();
	}


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

	//CIRCULO WANDER
	draw_circle(TheApp::Instance()->getRenderer(), (int)targetCircle.x, (int)targetCircle.y, 40, 255, 255, 0, 255);

	//CIRCULO WANDER
	draw_circle(TheApp::Instance()->getRenderer(), (int)targetRandom.x, (int)targetRandom.y, 10, 0, 0, 255, 255);
}

const char* SceneSeek::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}