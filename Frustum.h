#pragma once
#include <glm/glm.hpp>
#include "Plane3.h"

class Frustum
{
public:
	Frustum();
	~Frustum(void);

	void setFrustum(glm::mat4 &mat);
	
	bool cubeInFrustum(glm::vec3 &center, float size);
	bool pointInFrustum(glm::vec3 &point);
	bool sphereInFrustum(glm::vec3 &center, float radius);

private:
	Plane3 planes[6];
};

