#pragma once
#include "Transform.h"
#include "PhysicsObject.h"
#include <glm/vec4.hpp>
class GameObject
{
public:
	GameObject()
	{
		active = true;
		physicsObject = new PhysicsObject(&transform);
	}

	virtual ~GameObject()
	{
		delete physicsObject;
	}

	virtual void WhenCollided(int col) = 0;
	bool active;
	Transform transform;
	PhysicsObject* physicsObject;

	glm::vec4 colour;
protected:
};