#include "ScenePath.h"
#include "Seek.h"
#include "Pursue.h"
#include "ScenePath.h"

using namespace std;

ScenePath::ScenePath() {

	path[0] = Vector2D(500.f, 200.f);
	path[1] = Vector2D(120.f, 125.f);
	path[2] = Vector2D(500.f, 450.f);
	path[3] = Vector2D(350.f, 700.f);
	path[4] = Vector2D(900.f, 425.f);
	path[5] = Vector2D(1200.f, 700.f);

	Agent* agent = new Agent;
	agent->setBehavior(new Pursue);
	agent->SetId(0);
	agent->setPosition(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->indexCurrentAgent = GetParameter(agent->getPosition());
	agents.push_back(agent);
}

ScenePath::~ScenePath() {
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
}

int ScenePath::GetParameter(Vector2D position) {
	int minId = 0;
	float minDist = Vector2D::Distance(position, path[0]);
	for (int i = 1; i < 6; i++) {
		if (Vector2D::Distance(position, path[i]) <= minDist) {
			minDist = Vector2D::Distance(position, path[i]);
			minId = i;
		}
	}

	return minId;
}

void ScenePath::update(float dtime, SDL_Event* event) {

	target = path[agents[0]->indexCurrentAgent];
	agents[0]->setTarget(target);
	//target = Vector2D(0, 0);
	if (Vector2D::Distance(agents[0]->getPosition(), target) < 30.f) {
		agents[0]->indexCurrentAgent++;
	}

	//Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], target, dtime);
	//agents[0]->update(steering_force, dtime, event);
	agents[0]->update(dtime, event);

}

void ScenePath::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();

	draw_circle(TheApp::Instance()->getRenderer(), path[0].x, path[0].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[1].x, path[1].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[2].x, path[2].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[3].x, path[3].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[4].x, path[4].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[5].x, path[5].y, 15, 255, 255, 255, 255);
}

const char* ScenePath::getTitle() {
	return "SDL Steering Behaviors :: Path Following Demo";
}