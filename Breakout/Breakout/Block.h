#pragma once
#include "GameObject.h"
#include "CollisionBox.h"

class Game;
class PhysicsObject;

class Block : public GameObject
{
public:
	Block(glm::vec2 pos, glm::vec2 scale, Game* g)
	{
		game = g;
		transform.position = pos;
		transform.scale = scale;
		physicsObject->collisionVolume = new CollisionBox({transform.scale.x / 2.f, transform.scale.y / 2.f});
		physicsObject->tag = PhysicsObject::CollisionTag::BLOCK;

	}

	~Block()
	{
		delete physicsObject->collisionVolume;
	}

	void WhenCollided(int col) override;

protected:
	Game* game;
private:
	void SpawnPowerUp();
};

class Wall : public Block
{
public:
	Wall(glm::vec2 pos, glm::vec2 scale) : Block(pos, scale, nullptr)
	{

	}

	~Wall()
	{
	}

	void WhenCollided(int col) override
	{
	}


};

class KillFloor : public Block
{
public:
	KillFloor(glm::vec2 pos, glm::vec2 scale, Game* g) : Block(pos, scale, g)
	{
		physicsObject->tag = PhysicsObject::CollisionTag::KILL_FLOOR;
	}

	~KillFloor()
	{

	}

	void WhenCollided(int col) override;


};