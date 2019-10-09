#include "SceneSeekFlee.h"
#include "Seek.h"
#include "Flee.h"
#include "Flocking.h"

using namespace std;

SceneSeekFlee::SceneSeekFlee()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->SetId(0);
	agent->setPosition(Vector2D(900, 50));
	//agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.5);
	agent->setVelocity(Vector2D(50, 100));
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);

	//NEW ZOMBIES
	Agent* agent1 = new Agent;
	agent1->setBehavior(new Flocking);
	agent1->SetId(1);
	agent1->setPosition(Vector2D(140, 600));
	//agent1->setTarget(Vector2D(640, 360));
	agent1->setMass(0.5);
	agent1->setVelocity(Vector2D(100, 100));
	agent1->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent1);

	/*ANOTHER ZOMBIE*/
	Agent* agent2 = new Agent;
	agent2->setBehavior(new Flocking);
	agent2->SetId(2);
	agent2->setPosition(Vector2D(200, 60));
	//agent2->setTarget(Vector2D(640, 360));
	agent2->setMass(0.5);
	agent2->setVelocity(Vector2D(150, 100));
	agent2->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent2);

	/*ANOTHER ZOMBIE*/
	Agent* agent3 = new Agent;
	agent3->setBehavior(new Flocking);
	agent3->SetId(3);
	//agent3->setTarget(Vector2D(640, 360));
	agent3->setPosition(Vector2D(100, 70));
	agent3->setMass(0.5);
	agent3->setVelocity(Vector2D(75, 75));
	agent3->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent3);

	/*ANOTHER ZOMBIE*/
	Agent* agent4 = new Agent;
	agent4->setBehavior(new Flocking);
	agent4->SetId(4);
	//agent3->setTarget(Vector2D(640, 360));
	agent4->setPosition(Vector2D(100, 70));
	agent4->setMass(0.5);
	agent4->setVelocity(Vector2D(75, 75));
	agent4->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent4);

	/*ANOTHER ZOMBIE*/
	Agent* agent5 = new Agent;
	agent5->setBehavior(new Flocking);
	agent5->SetId(5);
	//agent3->setTarget(Vector2D(640, 360));
	agent5->setPosition(Vector2D(350, 100));
	agent5->setMass(0.5);
	agent5->setVelocity(Vector2D(20, 100));
	agent5->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent5);

	/*ANOTHER ZOMBIE*/
	Agent* agent6 = new Agent;
	agent6->setBehavior(new Flocking);
	agent6->SetId(6);
	//agent3->setTarget(Vector2D(640, 360));
	agent6->setPosition(Vector2D(50, 250));
	agent6->setMass(0.5);
	agent6->setVelocity(Vector2D(60, 20));
	agent6->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent6);

	/*ANOTHER ZOMBIE*/
	Agent* agent7 = new Agent;
	agent7->setBehavior(new Flocking);
	agent7->SetId(7);
	//agent3->setTarget(Vector2D(640, 360));
	agent7->setPosition(Vector2D(90, 30));
	agent6->setMass(0.5);
	agent7->setVelocity(Vector2D(75, -75));
	agent7->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent7);

	//SOLDIERS
	/*agent = new Agent();
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(600,50));
	agent->setTarget(Vector2D(900, 650));
	agent->setMass(0.5);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent); 
	target = Vector2D(100, 100);*/

	//FLOKING
	/*neighborCount = 0;
	neighborRadius = 200;*/
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
	float K_separation_force = 1200.f;
	float K_cohesion_force = 1400.f;
	float K_alignment_force = 0.8;

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
	/*target = agents[1]->getPosition();
	agents[0]->setTarget(target);*/

	for (int i = 0; i < (int)agents.size(); i++)
	{
		//FLOCKING FOR ALL AGENTS
		agents[i]->separationDirection = agents[i]->FleeFlocking(agents[i], agents);
		agents[i]->cohesionDirection = agents[i]->SeekFlocking(agents[i], agents);
		agents[i]->alignmentDirection = agents[i]->FlocAligment(agents[i], agents);

		agents[i]->Flocking_Force = agents[i]->separationDirection * K_separation_force +
									agents[i]->cohesionDirection * K_cohesion_force +
									agents[i]->alignmentDirection * K_alignment_force;

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