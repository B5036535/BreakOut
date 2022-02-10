#pragma once
#include "GameObject.h"
#include "CollisionCircle.h"
#include <math.h>

class Ball : public GameObject
{
public:
	Ball()
	{
		transform.position = { 0,0 };
		physicsObject->collisionVolume = new CollisionCircle(transform.scale.x / 2.f);
		physicsObject->invMass = 0.5f;
		physicsObject->velocity = RandomDirection(0, 360.f) * INIT_SPEED;
		physicsObject->tag = PhysicsObject::CollisionTag::BALL;
		numOfGrows = 0;
		colour = { 1.f,1.f,1.f,1.f };
	}

	Ball(glm::vec2 pos, float degrees_min, float degrees_max)
	{
		transform.position = pos;
		physicsObject->collisionVolume = new CollisionCircle(transform.scale.x / 2.f);
		physicsObject->invMass = 0.5f;
		physicsObject->velocity = RandomDirection(degrees_min, degrees_max) * INIT_SPEED;
		physicsObject->tag = PhysicsObject::CollisionTag::BALL;
		numOfGrows = 0;
		colour = { 1.f,1.f,1.f,1.f };
	}

	virtual ~Ball()
	{
		delete physicsObject->collisionVolume;
	}

	void UpdateDimensions(float delta)
	{
		if (delta >= 0 && numOfGrows >= MAX_NUM_OF_GROWS)
			return;

		transform.scale *= delta;
		physicsObject->collisionVolume->UpdateDimensions(transform.scale.x / 2.f);
		numOfGrows += delta >= 0 ? 1 : -1;
	}



	//starts at {0,1}
	glm::vec2 RandomDirection(float min, float max)
	{
		float rnd = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		float rads = (rnd * (max - min) + min) * (3.14159265359 / 180.f);

		return glm::vec2(sin(rads), cos(rads));
	}

	void WhenCollided(int col) override 
	{
		if (col == 5)
			active = false;
	}

protected:
	const float INIT_SPEED = 15.f;

	int numOfGrows;
	const int MAX_NUM_OF_GROWS = 3;
};