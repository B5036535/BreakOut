#include "PhysicsSystem.h"

void PhysicsSystem::PhysicsUpdate(float dt)
{
	CollisionCheck();
	IntergrateVelocities(dt);
}

void PhysicsSystem::CollisionCheck()
{
	NarrowPhase();
}

void PhysicsSystem::BroadPhase()
{

}

void PhysicsSystem::NarrowPhase()
{
	for (int i = 0; i < Balls.size(); i++)
	{
		for (int j = i + 1; j < Balls.size(); j++)
		{

		}

		for (auto block : Blocks)
		{

		}
	}
}

void PhysicsSystem::ResolveCollision()
{

}

void PhysicsSystem::IntergrateVelocities(float dt)
{

}