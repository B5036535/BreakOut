#pragma once
#include "PhysicsSystem.h"
#include "Renderer.h"
#include <vector>

class GLFWwindow;
class Block;
class Ball;
class Player;
class Game
{
public:
	Game(GLFWwindow* w, const uint32_t width, const uint32_t height) : renderer(w, this, width, height), physics(this), WIDTH(width), HEIGHT(height)
	{
		window = w;
		state = GameState::PLAYING;
		InitGame();
		InitLevel();
	}

	~Game()
	{
		delete player;

		for (Ball* ball : balls)
			delete ball;
		balls.clear();

		for (Block* block : blocks)
			delete block;

		blocks.clear();
	}

	Player* player;
	std::vector<Block*> blocks;
	std::vector<Ball*> balls;

	void Update(float dt);

	void ResetGame();
private:
	enum GameState {PLAYING, PAUSED, LOST, WON};

	GameState state;

	Renderer renderer;
	PhysicsSystem physics;

	GLFWwindow* window;
	const uint32_t WIDTH;
	const uint32_t HEIGHT;

	const int NUM_OF_ROWS = 7;
	const int NUM_OF_COLS = 11;
	const glm::vec2 BLOCK_SPACING = { 6.0f, 2.5f };
	const glm::vec2 BLOCK_OFFSET = { -30.f, 10.f };
	const glm::vec2 BALL_OFFSET = { 0, 5.f};

	void InitGame();
	void InitLevel();
	void Playing(float dt);
	void UpdateGameObjects(float dt);
	void Paused();
	void Lost();
	void Won();
};