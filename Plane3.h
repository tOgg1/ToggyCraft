#pragma once
#include <glm/glm.hpp>

#include "Math.h"

class Plane3
{
public:
	Plane3(void);
	~Plane3(void);

	float distanceTo(glm::vec3 point);
	float a, b, c, d;
};

