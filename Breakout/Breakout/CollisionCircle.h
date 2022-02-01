#pragma once
#include "CollisionVolume.h"

class CollisionCircle : public CollisionVolume
{
public:
	CollisionCircle(float r)
	{
		type = VolumeType::CIRCLE;
		radius = r;
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