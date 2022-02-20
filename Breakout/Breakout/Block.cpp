#include "Block.h"
#include "Game.h"
#include "PowerUps.h"
#include <algorithm>


void Block::WhenCollided(int col)
{
	if (col == 3)
	{
		active = false;
		SpawnPowerUp();
		game->score++;
	}
}

void Block::SpawnPowerUp()
{
	int rnd = rand() % 100;
	
	if (rnd < 10)
	{
		int rndStart = rand() % game->powerUps.size();
		
		
		auto it = std::find_if(game->powerUps.begin() + rndStart, game->powerUps.end(), [&](PowerUp* p) -> bool {return !p->active; });
		if (it != game->powerUps.end())
		{
			(*it)->Spawn(transform.position);
		}
		else
		{
			it = std::find_if(game->powerUps.begin(), game->powerUps.begin() + rndStart, [&](PowerUp* p) -> bool {return !p->active; });
			if (it != game->powerUps.begin() + rndStart)
			{
				(*it)->Spawn(transform.position);
			}
		}
	}
}

void KillFloor::WhenCollided(int col)
{
	if (col == 3)
	{
		game->ballCounter--;
	}
}
