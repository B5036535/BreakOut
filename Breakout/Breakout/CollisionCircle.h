#pragma once
#include "CollisionVolume.h"

class CollisionCircle : public CollisionVolume
{
public:
	CollisionCircle()
	{
		type = VolumeType::CIRCLE;
	}

	~CollisionCircle()
	{

	}

	void UpdateDimensions(float delta)
	{
		radius *= delta;
	}

private:

	float radius;
};