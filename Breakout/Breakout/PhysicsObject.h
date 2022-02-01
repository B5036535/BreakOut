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
		collision = CollisionTag::NONE;
		transform = transf;
	}

	virtual ~PhysicsObject()
	{

	}

	enum CollisionTag {NONE = 0,PLAYER = 1, BLOCK = 2, BALL = 3};
	CollisionTag collision;
	CollisionTag Tag;

	CollisionVolume* collisionVolume;

	float invMass = 0.f;
	float elasticity = 1.3f;

	glm::vec2 force;
	glm::vec2 velocity;

	Transform* transform;

	void ApplyLinearImpulse(glm::vec2 impulse)
	{
		velocity += impulse * invMass;
	}
};