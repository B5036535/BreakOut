#pragma once
#include <glm/vec2.hpp>

class GameObject;
class CollisionVolume;
struct Transform;

class PhysicsObject
{
public:
	PhysicsObject(Transform* transf)
	{
		active = true;

		transform = transf;
	}

	virtual ~PhysicsObject()
	{

	}


	bool active;

	CollisionVolume* collisionVolume;

	float invMass;
	float elasticity;

	glm::vec2 force;
	glm::vec2 velocity;

	Transform* transform;

	void ApplyLinearImpulse(glm::vec2 impulse)
	{
		velocity += impulse * invMass;
	}
};