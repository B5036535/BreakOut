#pragma once
#include "CollisionVolume.h"
#include <glm/vec2.hpp>

class GameObject;

class PhysicsObject
{
public:
	PhysicsObject(GameObject* go)
	{
		active = true;
		gameObject = go;
	}

	virtual ~PhysicsObject()
	{

	}

	GameObject* gameObject;

	bool active;
	CollisionVolume* collisionVolume;
	float invMass;
	float elasticity;
	glm::vec2 force;
	glm::vec2 velocity;
	glm::vec2 position;

	void ApplyLinearImpulse(glm::vec2 impulse)
	{
		velocity += impulse * invMass;
	}

};