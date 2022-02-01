#pragma once
#include "CollisionDetection.h"
#include "PhysicsObject.h"

#include <vector>
class Game;
class PhysicsSystem
{
public:
	PhysicsSystem(Game* g)
	{
		game = g;
	}

	~PhysicsSystem()
	{
	}

	void PhysicsUpdate(float dt);
private:
	CollisionDetection collisionDetection;

	void CollisionCheck();
	void BroadPhase();
	void NarrowPhase();
	void ResolveCollision(CollisionInfo* info);

	void IntergrateVelocities(float dt);

	Game* game;
};