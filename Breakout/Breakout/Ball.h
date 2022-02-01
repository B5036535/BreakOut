#pragma once
#include "GameObject.h"
#include "CollisionCircle.h"
#include <math.h>

class Ball : public GameObject
{
public:
	Ball(glm::vec2 pos)
	{
		transform.position = pos;
		physicsObject->collisionVolume = new CollisionCircle(transform.scale.x / 2.f);
		physicsObject->invMass = 0.5f;
		physicsObject->velocity = RandomDirection(-70.f, 70.f) * INIT_SPEED;
	}

	~Ball()
	{
		delete physicsObject->collisionVolume;
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
		physicsObject->collision = PhysicsObject::CollisionTag::NONE;
	}
protected:
	const float INIT_SPEED = 0.5f;
};