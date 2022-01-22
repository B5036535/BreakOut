#pragma once
#include "CollisionVolume.h"
#include <glm/vec2.hpp>
class CollisionBox : public CollisionVolume
{
public: 
	CollisionBox() 
	{
	}

	~CollisionBox()
	{
	
	}

	void UpdateDimensions(float delta)
	{
		halfDimensions.x *= delta;
		halfDimensions.y *= delta;
	}
	glm::vec2 halfDimensions;
private:
};