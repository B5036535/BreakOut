#pragma once
#include <glm/vec2.hpp>
struct Transform
{
	Transform()
	{
		position = { 0,0 };
		scale = { 1,1 };
	}

	glm::vec2 position;
	glm::vec2 scale;
};