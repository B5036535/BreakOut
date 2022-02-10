#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"
#include "PowerUps.h"

void Game::InitGame()
{
}

void Game::InitLevel()
{
	player = new Player(window, PLAYER_SPAWN, WIDTH);

	Wall* rWall = new Wall({ (float)WIDTH / 20.f, 0.f }, { 1.f, (float)HEIGHT / 10.f });
	Wall* lWall = new Wall({ -(float)WIDTH / 20.f, 0.f }, { 1.f, HEIGHT / 10.f });
	Wall* tWall = new Wall({ 0, (float)HEIGHT / 20.f }, { (float)WIDTH / 10.f, 1 });
	KillFloor* bFloor = new KillFloor({ 0, -(float)HEIGHT / 20.f }, { (float)WIDTH / 10.f, 1 }, this);
	rWall->colour = {1.f,1.f,1.f,1.f};
	lWall->colour = {1.f,1.f,1.f,1.f};
	tWall->colour = {1.f,1.f,1.f,1.f};
	bFloor->colour = {1.f,0.f,0.f,1.f};
	blocks.push_back(rWall);
	blocks.push_back(lWall);
	blocks.push_back(tWall);
	blocks.push_back(bFloor);

	for (int x = 0; x < NUM_OF_COLS; x++)
	{
		for (int y = 0; y < NUM_OF_ROWS; y++)
		{
			Block* block = new Block({ x * BLOCK_SPACING.x + BLOCK_OFFSET.x, y * BLOCK_SPACING.y + BLOCK_OFFSET.y }, BLOCK_SCALE, this);
			float rads = (static_cast<float>(y) / static_cast<float>(NUM_OF_ROWS)) * (3.14159265359f / 180.f);
			block->colour = { (static_cast<float>(y) / static_cast<float>(NUM_OF_ROWS)), 1.f ,1 - (static_cast<float>(y) / static_cast<float>(NUM_OF_ROWS)),1.f };
			blocks.push_back(block);
		}
	}

	InitBalls();
}

void Game::InitBalls()
{
	Ball* ball = new Ball(BALL_OFFSET, -70.f, 70.f);
	balls.push_back(ball);

	PowerUp_Accel accel;
	PowerUp_Deccel deccel;
	PowerUp_Grow grow;
	PowerUp_MultiBall multi;
	AddPowerUps(accel);
	AddPowerUps(deccel);
	AddPowerUps(grow);
	AddPowerUps(multi);
}

template<class T>
void Game::AddPowerUps(T p)
{
	for (int i = 0; i < 3; i++)
	{
		T* pUp = new T(this, BALL_OFFSET, 0.f, 360.f);
		powerUps.push_back(pUp);
		balls.push_back(pUp);
	}
}

void Game::Update(float dt)
{
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		releasedSpacebar = true;

	switch (state)
	{
	case GameState::PLAYING:
		Playing(dt);
		break;
	case GameState::PAUSED:
		Paused();
		break;
	case GameState::LOST:
		Lost();
		break;
	case GameState::WON:
		Won();
		break;
	}
	renderer.DrawFrame();
}

void Game::ResetGame()
{
	score = 0;

	for (auto block : blocks)
		block->active = true;

	for (Ball* ball : balls)
		delete ball;
	balls.clear();
	// PowerUps deleted in balls
	powerUps.clear();

	InitBalls();

	ballCounter = balls.size() - powerUps.size();

	player->transform.position = PLAYER_SPAWN;

	state = GameState::PLAYING;
	releasedSpacebar = true;
}

void Game::Playing(float dt)
{
	UpdateGameObjects(dt);
	physics.PhysicsUpdate(dt);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && releasedSpacebar)
	{
		state = GameState::PAUSED;
		releasedSpacebar = false;
	}
	else if (score >= MAX_SCORE)
		state = GameState::WON;
	else if (ballCounter <= 0)
		state = GameState::LOST;
}

void Game::UpdateGameObjects(float dt)
{
	player->UpdatePlayer();
	//Check if objs have been collided
	for (auto block : blocks)
	{
		if (block->physicsObject->collision > 0 && block->active)
			block->WhenCollided(block->physicsObject->collision);

		block->physicsObject->collision = PhysicsObject::CollisionTag::NONE;
	}
	for (auto ball : balls)
	{
		if(ball->physicsObject->collision > 0 && ball->active)
			ball->WhenCollided(ball->physicsObject->collision);

		ball->physicsObject->collision = PhysicsObject::CollisionTag::NONE;
	}

	if (new_balls.size() > 0)
	{
		for (auto new_ball : new_balls)
		{
			balls.push_back(new_ball);
		}

		new_balls.clear();
	}
}

void Game::Paused()
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && releasedSpacebar)
	{
		state = GameState::PLAYING;
		releasedSpacebar = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ResetGame();
}

void Game::Lost()
{
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ResetGame();
}

void Game::Won()
{
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ResetGame();
}
