#include "Agent.h"

using namespace std;

Agent::Agent() : sprite_texture(0),
				 position(Vector2D(100, 100)),
				 target(Vector2D(1000, 100)),
				 velocity(Vector2D(0, 0)),
				 velocityTarget(Vector2D(0.5, 0.5)),
				 mass(0.5),
				 max_force(50),
				 max_velocity(200),
				 orientation(0),
				 sprite_num_frames(0),
				 sprite_w(0),
				 sprite_h(0),
				 draw_sprite(false),
				 slowingRadius(200),
				 ExtremeSlowingRadius(50),
				 factor(100),
				 neighbor_Radius(50),
				 K_separation_force(300),
				 K_cohesion_force(200),
				 K_alignment_force(1),
				 Flocking_Force(10)
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior *behavior)
{
	steering_behaviour = behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

float Agent::getSlowingRadius()
{
	return slowingRadius;
}

float Agent::getFactor()
{
	return factor;
}

float Agent::getExtremeSlowingRadius()
{
	return ExtremeSlowingRadius;
}

void Agent::setFactor(float newFactor)
{
	factor = newFactor;
}

Vector2D Agent::getAcceleration()
{
	return acceleration;
}

Vector2D Agent::getVelocityTarget()
{
	return velocityTarget;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::setTargetVelocity(Vector2D NewvelocityTarget)
{
	velocityTarget = NewvelocityTarget;
}

void Agent::setAcceleration(Vector2D NewAcceleration)
{
	acceleration = NewAcceleration;
}

void Agent::setMass(float NewMass)
{
	mass = NewMass;
}

void Agent::update(float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);
	
	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}
}

Vector2D Agent::predictedPosition(Agent* seguidor, Agent* perseguido)
{
	float T = Vector2D::Distance(seguidor->getPosition(), perseguido->getPosition()) / seguidor->getMaxVelocity();
	Vector2D predictedTarget = perseguido->getPosition() + perseguido->getVelocity() * T;
	return predictedTarget;
}

Vector2D Agent::predictedPositionEvade(Agent* seguidor, Agent* perseguido)
{
	float T = Vector2D::Distance(seguidor->getPosition(), perseguido->getPosition()) / seguidor->getMaxVelocity();
	Vector2D predictedTarget = perseguido->getPosition() + perseguido->getVelocity() * T;
	return predictedTarget;
}

Vector2D Agent::FleeFlocking(Agent* agent, std::vector<Agent*> ArrayAgents)
{
	float neigborCount = 0;
	Vector2D separationVector = Vector2D(0, 0);
	Vector2D separationDirection = Vector2D(0, 0);
	Vector2D distanceBetweenVectors = Vector2D(0, 0);

	for (int i = 0; i < ArrayAgents.size(); i++)
	{
		distanceBetweenVectors = distanceBetweenVectors.Distance(ArrayAgents[i]->getPosition(), agent->getPosition());
		if (distanceBetweenVectors.Length() < neighbor_Radius)
		{
			separationVector += (agent->getPosition() - ArrayAgents[i]->getPosition());
			++neigborCount;
		}
	}

	separationVector /= neigborCount;
	separationDirection = separationVector.Normalize();

	//std::cout << "Separation Vector: X " << separationDirection.x << ", Y " << separationDirection.y;

	return separationDirection;
}

Vector2D Agent::SeekFlocking(Agent* agent, std::vector<Agent*> ArrayAgents)
{
	float neigborCount = 0;
	Vector2D averagePosition = Vector2D(0, 0);
	Vector2D cohesionDirection = Vector2D(0, 0);
	Vector2D distanceBetweenVectors = Vector2D(0, 0);

	for (int i = 0; i < ArrayAgents.size(); i++)
	{
		distanceBetweenVectors = distanceBetweenVectors.Distance(ArrayAgents[i]->getPosition(), agent->getPosition());
		if (distanceBetweenVectors.Length() < neighbor_Radius)
		{
			averagePosition += ArrayAgents[i]->getPosition();
			++neigborCount;
		}
	}

	averagePosition /= neigborCount;
	averagePosition -= agent->getPosition();
	cohesionDirection = averagePosition.Normalize();

	return cohesionDirection;
}

Vector2D Agent::FlocAligment(Agent* agent, std::vector<Agent*> ArrayAgents)
{
	float neigborCount = 0;
	Vector2D averageVelocity = Vector2D(0, 0);
	Vector2D alignmentDirection = Vector2D(0, 0);
	Vector2D distanceBetweenVectors = Vector2D(0, 0);

	for (int i = 0; i < ArrayAgents.size(); i++)
	{
		distanceBetweenVectors = distanceBetweenVectors.Distance(ArrayAgents[i]->getPosition(), agent->getPosition());
		if (distanceBetweenVectors.Length() < neighbor_Radius)
		{
			averageVelocity += ArrayAgents[i]->getVelocity();
			++neigborCount;
		}
	}

	averageVelocity /= neigborCount;
	alignmentDirection = averageVelocity.Normalize();

	return alignmentDirection;
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}
