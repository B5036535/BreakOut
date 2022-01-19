#pragma once
#include "GameObject.h"

class PhysicsObject;
class Ball : public GameObject
{
public:
	Ball()
	{

	}

	~Ball()
	{
		delete physObj;
	}
protected:
	float init_speed = 0.1f;
	PhysicsObject* physObj;
};