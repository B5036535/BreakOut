#pragma once
#include "GameObject.h"
#include "CollisionBox.h"
class PhysicsObject;

class Block : public GameObject
{
public:
	Block()
	{
		physicsObject->collisionVolume = new CollisionBox();
	}

	~Block()
	{
		delete physicsObject->collisionVolume;
	}
protected:
};