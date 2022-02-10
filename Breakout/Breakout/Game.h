#pragma once
#include "PhysicsSystem.h"
#include "Renderer.h"
#include <vector>

class GLFWwindow;
class Block;
class Ball;
class Player;
class PowerUp;
class Game
{
public:
	Game(GLFWwindow* w, const uint32_t width, const uint32_t height) : renderer(w, this, width, height), physics(this), WIDTH(width), HEIGHT(height)
	{
		window = w;
		state = GameState::PLAYING;
		InitGame();
		InitLevel();

		score = 0;
		ballCounter = balls.size() - powerUps.size();

		releasedSpacebar = true;
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

		// PowerUps deleted in balls
		powerUps.clear();
	}

	enum GameState {PLAYING, PAUSED, LOST, WON};

	Player* player;
	const glm::vec2 PLAYER_SPAWN = { 0, -25 };

	std::vector<Block*> blocks;
	int score;

	std::vector<Ball*> balls;
	std::vector<Ball*> new_balls;
	int ballCounter;

	std::vector<PowerUp*> powerUps;

	void Update(float dt);
	void ResetGame();

	GameState GetState() { return state; }
private:

	GameState state;

	Renderer renderer;
	PhysicsSystem physics;

	GLFWwindow* window;
	const uint32_t WIDTH;
	const uint32_t HEIGHT;

	const int NUM_OF_ROWS = 7;
	const int NUM_OF_COLS = 11;
	const int MAX_SCORE = NUM_OF_COLS * NUM_OF_ROWS;
	const glm::vec2 BLOCK_SPACING = { 6.0f, 2.5f };
	const glm::vec2 BLOCK_OFFSET = { -30.f, 10.f };
	const glm::vec2 BLOCK_SCALE = { 5.f, 1.f };

	/////Debug Setup
	///const int NUM_OF_ROWS = 1;
	///const int NUM_OF_COLS = 1;
	///const int MAX_SCORE = NUM_OF_COLS * NUM_OF_ROWS;
	///const glm::vec2 BLOCK_SPACING = { 6.0f, 2.5f };
	///const glm::vec2 BLOCK_OFFSET = { 0.f, 10.f };
	///const glm::vec2 BLOCK_SCALE = { 30.f, 1.f };

	const glm::vec2 BALL_OFFSET = { 0, -5.f};

	bool releasedSpacebar;

	void InitGame();
	void InitLevel();
	void InitBalls();
	template<class T>
	void AddPowerUps(T p);
	void Playing(float dt);
	void UpdateGameObjects(float dt);
	void Paused();
	void Lost();
	void Won();
};

