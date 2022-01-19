#pragma once
#include "CollisionVolume.h"

class CollisionBox : public CollisionVolume
{
public: 
	CollisionBox() 
	{
		type = VolumeType::BOX;
	}

	~CollisionBox()
	{
	
	}

	void UpdateDimensions(float delta)
	{
		halfDimensions[0] *= delta;
		halfDimensions[1] *= delta;
	}
private:
	float halfDimensions[2];
};