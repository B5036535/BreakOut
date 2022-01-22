#pragma once
#include <glm/vec2.hpp>

class PhysicsObject;
class CollisionBox;
class CollisionCircle;

struct CollisionInfo
{
	CollisionInfo()
	{
		a = nullptr;
		b = nullptr;
		normal = {0,0};
		penetration = 0.f;
	}
	PhysicsObject* a;
	PhysicsObject* b;
	glm::vec2 normal;
	float penetration;
};

class CollisionDetection
{
public:
	CollisionDetection()
	{
		currentCollisionInfo = new CollisionInfo();
		currentPhysA = nullptr;
		currentPhysB = nullptr;
	}
	~CollisionDetection()
	{
		delete currentCollisionInfo;
	}
	CollisionInfo* currentCollisionInfo;
	PhysicsObject* currentPhysA;
	PhysicsObject* currentPhysB;

	bool HandleCollision(PhysicsObject* physA, PhysicsObject physB);
private:
	void FillCurrentInfo(PhysicsObject* physA, PhysicsObject* physB, glm::vec2 normal, float penetration);

	bool AABBTest(glm::vec2 posA, glm::vec2 posB, glm::vec2 halfSizeA, glm::vec2 halfSizeB);
	bool Intersection_AABB_AABB(CollisionBox* boxA, CollisionBox* boxB, glm::vec2 posA, glm::vec2 posB);
	bool Intersection_Circle_AABB(CollisionCircle* circle, CollisionBox* box, glm::vec2 posA, glm::vec2 posB);
	bool Intersection_Circle_Circle(CollisionCircle* circleA, CollisionCircle* circleB, glm::vec2 posA, glm::vec2 posB);
};