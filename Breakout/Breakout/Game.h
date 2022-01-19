#pragma once
class Game
{
public:
	Game()
	{

	}

	~Game()
	{

	}

	void Update(float dt);

	void ResetGame();
private:

	void InitLevel(int rows);
};