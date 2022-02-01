#include "CollisionDetection.h"
#include "PhysicsObject.h"
#include "CollisionBox.h"
#include "CollisionCircle.h"
#include "Transform.h"
#include <cmath>
#include <glm/geometric.hpp>
#include <algorithm>
using namespace glm;

bool CollisionDetection::HandleCollision(PhysicsObject* physA, PhysicsObject* physB)
{

	currentPhysA = physA;
	currentPhysB = physB;
	bool isABox = physA->collisionVolume->type == CollisionVolume::VolumeType::BOX;
	bool isBBox = physB->collisionVolume->type == CollisionVolume::VolumeType::BOX;
	
	vec2 posA = physA->transform->position;
	vec2 posB = physB->transform->position;

	if (isABox && isBBox)
		return Intersection_AABB_AABB(dynamic_cast<CollisionBox*>(physA->collisionVolume), dynamic_cast<CollisionBox*>(physB->collisionVolume), posA, posB);

	if (!isABox && isBBox)
		return Intersection_Circle_AABB(dynamic_cast<CollisionCircle*>(physA->collisionVolume), dynamic_cast<CollisionBox*>(physB->collisionVolume), posA, posB);

	if (isABox && !isBBox)
		return Intersection_Circle_AABB(dynamic_cast<CollisionCircle*>(physB->collisionVolume), dynamic_cast<CollisionBox*>(physA->collisionVolume), posB, posA);

	if (!isABox && !isBBox)
		return Intersection_Circle_Circle(dynamic_cast<CollisionCircle*>(physA->collisionVolume), dynamic_cast<CollisionCircle*>(physB->collisionVolume), posA, posB);

	return false;
}

void CollisionDetection::FillCurrentInfo(PhysicsObject* physA, PhysicsObject* physB, vec2 normal, float penetration)
{
	currentCollisionInfo->a = physA;
	currentCollisionInfo->b = physB;
	currentCollisionInfo->normal = normal;
	currentCollisionInfo->penetration = penetration;
}

bool CollisionDetection::AABBTest(vec2 posA, vec2 posB, vec2 halfSizeA, vec2 halfSizeB)
{
	vec2 delta = posB - posA;
	vec2 totalSize = halfSizeA + halfSizeB;

	return
		abs(delta.x) < totalSize.x
		&&
		abs(delta.y) < totalSize.y;
}

bool CollisionDetection::Intersection_AABB_AABB(CollisionBox* boxA, CollisionBox* boxB, vec2 posA, vec2 posB)
{

	if (AABBTest(posA, posB, boxA->halfDimensions, boxB->halfDimensions))
	{
		vec2 faces[] =
		{
			{-1, 0},
			{1, 0},
			{0, 1},
			{0, 1}
		};

		vec2 maxA = posA + boxA->halfDimensions;
		vec2 minA = posA - boxA->halfDimensions;
		vec2 maxB = posB + boxB->halfDimensions;
		vec2 minB = posB - boxB->halfDimensions;

		float distances[] =
		{
			maxB.x - minA.x,
			maxA.x - minB.x,
			maxB.y - minA.y,
			maxA.y - minB.y
		};

		float penetration = FLT_MAX;
		vec2 bestAxis;

		for (int i = 0; i < 4; i++)
		{
			if (distances[i] < penetration)
			{
				penetration = distances[i];
				bestAxis = faces[i];
			}
		}

		FillCurrentInfo(currentPhysA, currentPhysB, bestAxis, penetration);
		return true;
	}

	return false;
}

vec2 ClampVec2(vec2 input, vec2 min, vec2 max)
{
	return { std::clamp(input.x, min.x, max.x), std::clamp(input.y, min.y, max.y) };
}

bool CollisionDetection::Intersection_Circle_AABB(CollisionCircle* circle, CollisionBox* box, vec2 posA, vec2 posB)
{
	vec2 boxSize = box->halfDimensions;
	vec2 delta = posB - posA;
	vec2 closestPointOnBox = ClampVec2(delta, -boxSize, boxSize);
	
	vec2 localPoint = delta - closestPointOnBox;
	float distance = glm::length(localPoint);

	if (distance < circle->radius)
	{
		//collison resolution info
		vec2 normal = normalize(localPoint);
		float penetration = circle->radius - distance;

		FillCurrentInfo(currentPhysA, currentPhysB, normal, penetration);
		return true;
	}

	return false;
}

bool CollisionDetection::Intersection_Circle_Circle(CollisionCircle* circleA, CollisionCircle* circleB, vec2 posA, vec2 posB)
{
	float radiusA = circleA->radius;
	float radiusB = circleB->radius;

	float radii = radiusA + radiusB;
	vec2 delta = posB - posA;
	float deltaLength = glm::length(delta);


	if (deltaLength < radii)
	{
		//collision resolution info
		float penetration = radii - deltaLength;
		vec2 normal = normalize(delta);

		FillCurrentInfo(currentPhysA, currentPhysB, normal, penetration);
		return true;
	}

	return false;
}
