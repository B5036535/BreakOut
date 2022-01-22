#pragma once
#include "Transform.h"
#include "PhysicsObject.h"
class GameObject
{
public:
	GameObject()
	{
		physicsObject = new PhysicsObject(&transform);
	}

	virtual ~GameObject()
	{
		delete physicsObject;
	}

protected:
	PhysicsObject* physicsObject;
	Transform transform;
};