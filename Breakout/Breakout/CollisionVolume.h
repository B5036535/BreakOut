#pragma once
class CollisionVolume
{
public:
	CollisionVolume()
	{
	}

	virtual ~CollisionVolume()
	{

	}

	virtual void UpdateDimensions(float delta) = 0;
};