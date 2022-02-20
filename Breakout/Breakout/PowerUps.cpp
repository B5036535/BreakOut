#include "PowerUps.h"
#include "Game.h"
#include "CollisionCircle.h"


void PowerUp_Grow::WhenCollided(int col)
{
	if (col == 1)
	{
		for (auto ball : game->balls)
		{
			if (ball->active)
				ball->UpdateDimensions(2.f);
		}
		active = false;
	}

}

void PowerUp_MultiBall::WhenCollided(int col)
{
	if (col == 1)
	{

		float offset = -3.f;
		for (int i = 0; i < 3; i++)
		{
			Ball* ball = new Ball({ transform.position.x + offset,  game->PLAYER_SPAWN.y + 3.f }, -70.f, 70.f);
			game->new_balls.push_back(ball);
			game->ballCounter++;
			offset += 3.f;
		}
		active = false;
	}


}

void PowerUp_Deccel::WhenCollided(int col)
{
	if (col == 1)
	{
		for (auto ball : game->balls)
		{
			if (ball->active)
				ball->physicsObject->velocity /= 2.5f;
		}
		active = false;
	}


}

void PowerUp_Accel::WhenCollided(int col)
{
	if (col == 1)
	{
		for (auto ball : game->balls)
		{
			if(ball->active)
				ball->physicsObject->velocity *= 1.8f;
		}
		active = false;
	}


}

void PowerUp::Spawn(glm::vec2 pos)
{
	active = true;
	physicsObject->collision = PhysicsObject::CollisionTag::NONE;
	transform.position = pos;
	transform.scale = { 1,1 };
	physicsObject->collisionVolume->UpdateDimensions(transform.scale.x / 2.f);
	physicsObject->velocity = RandomDirection(110.f, 260.f) * INIT_SPEED;
}
