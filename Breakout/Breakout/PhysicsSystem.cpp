#include "PhysicsSystem.h"
#include "Transform.h"
#include "Game.h"
#include "Player.h"
#include "Ball.h"
#include "Block.h"
#include <glm/geometric.hpp>
#include <algorithm>
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
	for (int i = 0; i < game->balls.size(); i++)
	{
		for (int j = i + 1; j < game->balls.size(); j++)
		{
			if (game->balls[i]->active && game->balls[j]->active && collisionDetection.HandleCollision(game->balls[i]->physicsObject, game->balls[j]->physicsObject))
			{
				game->balls[i]->physicsObject->collision = PhysicsObject::CollisionTag::BALL;
				game->balls[j]->physicsObject->collision = PhysicsObject::CollisionTag::BALL;
				ResolveCollision(collisionDetection.currentCollisionInfo);
			}
		}

		for (auto block : game->blocks)
		{
			if (game->balls[i]->active && block->active && collisionDetection.HandleCollision(game->balls[i]->physicsObject, block->physicsObject))
			{
				game->balls[i]->physicsObject->collision = PhysicsObject::CollisionTag::BLOCK;
				block->physicsObject->collision = PhysicsObject::CollisionTag::BALL;
				ResolveCollision(collisionDetection.currentCollisionInfo);
			}
		}
	}
}

void PhysicsSystem::ResolveCollision(CollisionInfo* info)
{
	PhysicsObject* physA = info->a;
	PhysicsObject* physB = info->b;

	Transform* transformA = physA->transform;
	Transform* transformB = physB->transform;

	float totalMass = physA->invMass + physB->invMass;

	if (totalMass > 0)
	{
		transformA->position = transformA->position - glm::vec2(info->normal.x, info->normal.y) * info->penetration * (physA->invMass / totalMass);
		transformB->position = transformB->position + glm::vec2(info->normal.x, info->normal.y) * info->penetration * (physB->invMass / totalMass);
	}

	glm::vec2 contactVelocity = physB->velocity - physA->velocity;
	float impulseForce =glm::dot(contactVelocity, info->normal);

	float cRestitution = physA->elasticity * physB->elasticity;

	float j = (-(1.0f + cRestitution) * impulseForce) / totalMass;

	glm::vec2 fullImpulse = info->normal * j;

	physA->ApplyLinearImpulse(-fullImpulse);
	physB->ApplyLinearImpulse(fullImpulse);
}

void PhysicsSystem::IntergrateVelocities(float dt)
{
	game->player->transform.position.x = std::clamp(game->player->transform.position.x + game->player->physicsObject->velocity.x * dt,-game->player->MAX_DIST, game->player->MAX_DIST);

	for (auto ball : game->balls)
	{
		if (ball->active)
		{
			ball->transform.position += ball->physicsObject->velocity * dt;
		}
	}
}