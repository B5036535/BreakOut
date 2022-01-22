#pragma once
#include "CollisionVolume.h"

class CollisionCircle : public CollisionVolume
{
public:
	CollisionCircle()
	{

	}

	~CollisionCircle()
	{

	}

	void UpdateDimensions(float delta)
	{
		radius *= delta;
	}

	float radius;
private:
};