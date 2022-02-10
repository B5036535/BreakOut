#pragma once
#include "CollisionDetection.h"

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

	const float MAX_SPEED = 50.f;
};