#pragma once
class CollisionVolume
{
public:

	enum VolumeType {BOX, CIRCLE};

	VolumeType type;

	CollisionVolume()
	{
	}

	virtual ~CollisionVolume()
	{

	}

	virtual void UpdateDimensions(float delta) = 0;
};