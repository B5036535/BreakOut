#pragma once
#include "CollisionDetection.h"
#include <vector>
class PhysicsSystem
{
public:
	PhysicsSystem()
	{

		collisionDetection = new CollisionDetection();
	}

	~PhysicsSystem()
	{
		delete collisionDetection;
	}

	void PhysicsUpdate(float dt);
private:
	CollisionDetection* collisionDetection;

	void CollisionCheck();
	void BroadPhase();
	void NarrowPhase();
	void ResolveCollision();

	void IntergrateVelocities(float dt);
};