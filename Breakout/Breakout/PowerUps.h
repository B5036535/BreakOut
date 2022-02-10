#pragma once
#include "Ball.h"

class Game;
class PowerUp :public Ball
{
public:
	PowerUp()
	{
		game = nullptr;
		active = false;
		physicsObject->tag = PhysicsObject::CollisionTag::POWERUP;
	}

	PowerUp(Game* g, glm::vec2 pos, float degrees_min, float degrees_max) : Ball(pos, degrees_min, degrees_max)
	{
		game = g;
		active = false;
		physicsObject->tag = PhysicsObject::CollisionTag::POWERUP;
	}
	virtual ~PowerUp()
	{
	}

	void Spawn(glm::vec2 pos);
protected:
	Game* game;
};

class PowerUp_Grow :public PowerUp
{
public:
	PowerUp_Grow() : PowerUp(nullptr, { 0,0 }, 0.f, 0.f)
	{}

	PowerUp_Grow(Game* g, glm::vec2 pos, float degrees_min, float degrees_max) : PowerUp(g, pos, degrees_min, degrees_max)
	{
		colour = { 0.f,1.f,0.f,1.f };
	}
	PowerUp_Grow(const PowerUp_Grow& other)
	{
		colour = { 0.f,1.f,0.f,1.f };
	}
	~PowerUp_Grow()
	{
	}
	void WhenCollided(int col) override;

};

class PowerUp_MultiBall :public PowerUp
{
public:
	PowerUp_MultiBall () : PowerUp(nullptr, { 0,0 }, 0.f, 0.f)
	{}
	PowerUp_MultiBall(Game* g, glm::vec2 pos, float degrees_min, float degrees_max) : PowerUp(g, pos, degrees_min, degrees_max)
	{
		colour = { 0.f,0.f,1.f,1.f };
	}
	PowerUp_MultiBall(const PowerUp_MultiBall& other)
	{
		colour = { 0.f,0.f,1.f,1.f };
	}
	~PowerUp_MultiBall()
	{
	}
	void WhenCollided(int col) override;

};

class PowerUp_Deccel :public PowerUp
{
public:
	PowerUp_Deccel() : PowerUp(nullptr, { 0,0 }, 0.f, 0.f)
	{}
	PowerUp_Deccel(Game* g, glm::vec2 pos, float degrees_min, float degrees_max) : PowerUp(g, pos, degrees_min, degrees_max)
	{
		colour = { 1.f,0.f,0.f,1.f };
	}
	PowerUp_Deccel(const PowerUp_Deccel& other)
	{
		colour = { 1.f,0.f,0.f,1.f };
	}

	~PowerUp_Deccel()
	{
	}
	void WhenCollided(int col) override;
};

class PowerUp_Accel :public PowerUp
{
public:
	PowerUp_Accel() : PowerUp(nullptr, { 0,0 }, 0.f, 0.f)
	{}
	PowerUp_Accel(Game* g, glm::vec2 pos, float degrees_min, float degrees_max) : PowerUp(g, pos, degrees_min, degrees_max)
	{
		colour = { 0.f,1.f,1.f,1.f };
	}
	PowerUp_Accel(const PowerUp_Accel& other)
	{
		colour = { 0.f,1.f,1.f,1.f };
	}

	~PowerUp_Accel()
	{
	}
	void WhenCollided(int col) override;
};