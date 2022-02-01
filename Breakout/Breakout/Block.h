#pragma once
#include "GameObject.h"
#include "CollisionBox.h"
class PhysicsObject;

class Block : public GameObject
{
public:
	Block(glm::vec2 pos, glm::vec2 scale)
	{
		transform.position = pos;
		transform.scale = scale;
		physicsObject->collisionVolume = new CollisionBox({transform.scale.x / 2.f, transform.scale.y / 2.f});
	}

	~Block()
	{
		delete physicsObject->collisionVolume;
	}

	void WhenCollided(int col) override
	{
		active = false;
	}
protected:
};

class Wall : public Block
{
public:
	Wall(glm::vec2 pos, glm::vec2 scale) : Block(pos, scale)
	{

	}

	~Wall()
	{
	}

	void WhenCollided(int col) override
	{
	}
};