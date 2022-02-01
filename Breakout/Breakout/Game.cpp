#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"

void Game::InitGame()
{
}

void Game::InitLevel()
{
	player = new Player(window, {0, -20}, WIDTH);


	Wall* rWall = new Wall({ (float)WIDTH / 20.f, 0.f }, {1.f, (float)HEIGHT / 10.f});
	Wall* lWall = new Wall({ -(float)WIDTH / 20.f, 0.f }, {1.f, HEIGHT / 10.f});
	Wall* tWall = new Wall({0, (float)HEIGHT / 20.f }, { (float)WIDTH / 10.f, 1});
	Wall* bWall = new Wall({0, -(float)HEIGHT / 20.f }, { (float)WIDTH / 10.f, 1});
	blocks.push_back(rWall); 
	blocks.push_back(lWall); 
	blocks.push_back(tWall); 
	blocks.push_back(bWall);

	for (int x = 0; x < NUM_OF_COLS; x++)
	{
		for (int y = 0; y < NUM_OF_ROWS; y++)
		{
			Block* block = new Block({ x * BLOCK_SPACING.x + BLOCK_OFFSET.x, y * BLOCK_SPACING.y + BLOCK_OFFSET.y }, {5.f, 1.f});
			blocks.push_back(block);
		}
	}

	Ball* ball = new Ball(BALL_OFFSET);
	balls.push_back(ball);
}

void Game::Update(float dt)
{
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
}

void Game::Playing(float dt)
{
	UpdateGameObjects(dt);
	physics.PhysicsUpdate(dt);
}

void Game::UpdateGameObjects(float dt)
{
	player->UpdatePlayer();
	//Check if objs have been collided
	for (auto block : blocks)
	{
		if (block->physicsObject->collision > 0)
			block->WhenCollided(block->physicsObject->collision);
	}
	for (auto ball : balls)
	{
		if(ball->physicsObject->collision > 0)
			ball->WhenCollided(ball->physicsObject->collision);
	}
}

void Game::Paused()
{
}

void Game::Lost()
{
}

void Game::Won()
{
}
