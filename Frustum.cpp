#include "Frustum.h"


Frustum::Frustum(void)
{
	
}


Frustum::~Frustum(void)
{

}

void Frustum::setFrustum(glm::mat4 &mat)
{
	// Extracting with the Gribb/Hartman method: http://www.cs.otago.ac.nz/postgrads/alexis/planeExtraction.pdf
	if(!&mat)
		return;
		
	//left
	planes[0].a = mat[3][0] + mat[0][0];
	planes[0].b = mat[3][1] + mat[0][1];
	planes[0].c = mat[3][2] + mat[0][2];
	planes[0].d = mat[3][3] + mat[0][3];

	//right
	planes[1].a = mat[3][0] - mat[0][0];
	planes[1].b = mat[3][1] - mat[0][1];
	planes[1].c = mat[3][2] - mat[0][2];
	planes[1].d = mat[3][3] - mat[0][3];

	//bottom
	planes[2].a = mat[3][0] + mat[2][0];
	planes[2].b = mat[3][1] + mat[2][1];
	planes[2].c = mat[3][2] + mat[2][2];
	planes[2].d = mat[3][3] + mat[2][3];

	//top
	planes[3].a = mat[3][0] - mat[2][0];
	planes[3].b = mat[3][1] - mat[2][1];
	planes[3].c = mat[3][2] - mat[2][2];
	planes[3].d = mat[3][3] - mat[2][3];
	
	//near
	planes[4].a = mat[3][0] + mat[2][0];
	planes[4].b = mat[3][1] + mat[2][1];
	planes[4].c = mat[3][2] + mat[2][2];
	planes[4].d = mat[3][3] + mat[2][3];

	//far
	planes[5].a = mat[3][0] - mat[0][0];
	planes[5].b = mat[3][1] - mat[0][1];
	planes[5].c = mat[3][2] - mat[0][2];
	planes[5].d = mat[3][3] - mat[0][3];

	/*//left
	planes[0].a = mat[4][1] + mat[1][1];
	planes[0].b = mat[4][2] + mat[1][2];
	planes[0].c = mat[4][3] + mat[1][3];
	planes[0].d = mat[4][4] + mat[1][4];

	//right
	planes[1].a = mat[4][1] - mat[1][1];
	planes[1].b = mat[4][2] - mat[1][2];
	planes[1].c = mat[4][3] - mat[1][3];
	planes[1].d = mat[4][4] - mat[1][4];

	//bottom
	planes[2].a = mat[4][1] + mat[2][1];
	planes[2].b = mat[4][2] + mat[2][2];
	planes[2].c = mat[4][3] + mat[2][3];
	planes[2].d = mat[4][4] + mat[2][4];

	//top
	planes[3].a = mat[4][1] - mat[2][1];
	planes[3].b = mat[4][2] - mat[2][2];
	planes[3].c = mat[4][3] - mat[2][3];
	planes[3].d = mat[4][4] - mat[2][4];
	
	//near
	planes[4].a = mat[4][1] + mat[3][1];
	planes[4].b = mat[4][2] + mat[3][2];
	planes[4].c = mat[4][3] + mat[3][3];
	planes[4].d = mat[4][4] + mat[3][4];

	//far
	planes[5].a = mat[4][1] - mat[1][1];
	planes[5].b = mat[4][2] - mat[1][2];
	planes[5].c = mat[4][3] - mat[1][3];
	planes[5].d = mat[4][4] - mat[1][4];*/
}
	
bool Frustum::cubeInFrustum(glm::vec3 &center, float size)
{
	// Add case for when the cube is larger than the frustum
	glm::vec3 p1, p2, p3, p4, p5, p6, p7, p8;
	bool hasPointIn = false;
	
	p1 = glm::vec3(center.x + size, center.y + size, center.z + size);
	p2 = glm::vec3(center.x - size, center.y + size, center.z + size);
	p3 = glm::vec3(center.x + size, center.y - size, center.z + size);
	p4 = glm::vec3(center.x - size, center.y - size, center.z + size);
	p5 = glm::vec3(center.x + size, center.y + size, center.z - size);
	p6 = glm::vec3(center.x - size, center.y + size, center.z - size);
	p7 = glm::vec3(center.x + size, center.y - size, center.z - size);
	p8 = glm::vec3(center.x - size, center.y - size, center.z - size);

	hasPointIn &= pointInFrustum(p1);
	hasPointIn &= pointInFrustum(p2);
	hasPointIn &= pointInFrustum(p3);
	hasPointIn &= pointInFrustum(p4);
	hasPointIn &= pointInFrustum(p5);
	hasPointIn &= pointInFrustum(p6);
	hasPointIn &= pointInFrustum(p7);
	hasPointIn &= pointInFrustum(p8);

	return hasPointIn;
}

bool Frustum::pointInFrustum(glm::vec3 &point)
{
	return planes[0].distanceTo(point) > 0 && 
		   planes[1].distanceTo(point) > 0 && 
		   planes[2].distanceTo(point) > 0 && 
		   planes[3].distanceTo(point) > 0 && 
		   planes[4].distanceTo(point) > 0 && 
		   planes[5].distanceTo(point) > 0;
}

bool Frustum::sphereInFrustum(glm::vec3 &center, float radius)
{
	return planes[0].distanceTo(center) < radius ||
		   planes[1].distanceTo(center) > radius || 
		   planes[2].distanceTo(center) > radius ||
		   planes[3].distanceTo(center) > radius || 
		   planes[4].distanceTo(center) > radius || 
		   planes[5].distanceTo(center) > radius;	
}
