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

	enum VolumeType
	{
		BOX, CIRCLE
	};

	VolumeType type;

	virtual void UpdateDimensions(float delta) = 0;
};