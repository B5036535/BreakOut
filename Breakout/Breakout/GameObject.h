#pragma once
#include <glm/vec2.hpp>

#include "PhysicsObject.h"
class GameObject
{
public:
	GameObject()
	{
		physicsObject = new PhysicsObject(this);
	}

	virtual ~GameObject()
	{
		delete physicsObject;
	}

protected:
	PhysicsObject* physicsObject;
	glm::vec2 position;
};