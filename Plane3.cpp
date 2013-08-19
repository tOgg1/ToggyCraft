#include "Plane3.h"

Plane3::Plane3()
{

}


Plane3::~Plane3(void)
{

}

float Plane3::distanceTo(glm::vec3 point)
{
	return (a*point.x + b*point.y + c*point.z + d)*invSqrt(a*a + b*b + c*c);
}

