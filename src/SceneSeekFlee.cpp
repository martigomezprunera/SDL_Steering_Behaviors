#include "SceneSeekFlee.h"
#include "Seek.h"
#include "Flee.h"
#include "Flocking.h"

using namespace std;

SceneSeekFlee::SceneSeekFlee()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->setPosition(Vector2D(120, 50));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.5);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);

	//NEW ZOMBIES
	Agent* agent1 = new Agent;
	agent1->setBehavior(new Flocking);
	agent1->setPosition(Vector2D(140, 75));
	agent1->setTarget(Vector2D(640, 360));
	agent1->setMass(0.5);
	agent1->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent1);

	/*ANOTHER ZOMBIE*/
	Agent* agent2 = new Agent;
	agent2->setBehavior(new Flocking);
	agent2->setPosition(Vector2D(160, 60));
	agent2->setTarget(Vector2D(640, 360));
	agent2->setMass(0.5);
	agent2->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent2);

	/*ANOTHER ZOMBIE*/
	Agent* agent3 = new Agent;
	agent3->setBehavior(new Flocking);
	agent3->setTarget(Vector2D(640, 360));
	agent3->setPosition(Vector2D(100, 70));
	agent3->setMass(0.5);
	agent3->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent3);

	//SOLDIERS
	agent = new Agent();
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(600,50));
	agent->setTarget(Vector2D(900, 650));
	agent->setMass(0.5);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent); 
	target = Vector2D(100, 100);

	//FLOKING
	neighborCount = 0;
	neighborRadius = 60;
}

SceneSeekFlee::~SceneSeekFlee()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneSeekFlee::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
		}
		break;
	default:
		break;
	}
	target = agents[1]->getPosition();
	agents[0]->setTarget(target);

	//SETEMAOS LA VELOCIDAD DE LOS ZOMBIES CADA X TIEMPO
	for (int i = 0; i < agents.size(); i++)
	{
		agents[i]->setVelocity(Vector2D(100, 50));
	}

	for (int i = 0; i < (int)agents.size(); i++)
	{
		//FLOCKING FOR ALL AGENTS
		agents[i]->separationDirection = agents[i]->FleeFlocking(agents[i], agents);
		agents[i]->cohesionDirection = agents[i]->SeekFlocking(agents[i], agents);
		agents[i]->alignmentDirection = agents[i]->FlocAligment(agents[i], agents);

		agents[i]->Flocking_Force = agents[i]->separationDirection * agents[i]->K_separation_force +
									agents[i]->cohesionDirection * agents[i]->K_cohesion_force +
									agents[i]->alignmentDirection * agents[i]->K_alignment_force;

		agents[i]->update(dtime, event);
	}
	
}

void SceneSeekFlee::draw()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneSeekFlee::getTitle()
{
	return "SDL Steering Behaviors :: Seek and Flee Demo";
}