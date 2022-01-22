#pragma once
#include "GameObject.h"
#include "CollisionCircle.h"

class Ball : public GameObject
{
public:
	Ball()
	{
		physicsObject->collisionVolume = new CollisionCircle();
	}

	~Ball()
	{
		delete physicsObject->collisionVolume;
	}
protected:
	float init_speed = 0.1f;
};