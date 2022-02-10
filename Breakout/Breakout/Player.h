#pragma once
#include "GameObject.h"
#include "CollisionBox.h"
#include "GLFW/glfw3.h"
class Player : public GameObject
{
public:
	Player(GLFWwindow* w, glm::vec2 pos, const int width) : MAX_DIST(((float)width / 2.f) / 10.f - 2.5f)
	{
		window = w;
		transform.position = pos;
		transform.scale = { 5.f, 1.f };
		physicsObject->collisionVolume = new CollisionBox({ transform.scale.x / 2.f, transform.scale.y / 2.f });
		physicsObject->tag = PhysicsObject::CollisionTag::PLAYER;

		colour = { 0.2f, 0.2f, 1.f, 1.f };
	}

	~Player()
	{

	}

	void UpdatePlayer()
	{
		int dir = 0;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			dir += 1;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			dir -= 1;
		
		physicsObject->velocity = glm::vec2(dir, 0) * SPEED;
	}

	void WhenCollided(int col) override
	{
		physicsObject->collision = PhysicsObject::CollisionTag::NONE;
	}


	const float MAX_DIST;

private:
	GLFWwindow* window;

	const float SPEED = 40.f;
};