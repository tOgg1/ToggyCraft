#pragma once

#include <glm/glm.hpp>
#include "Game.h"
#include "Frustum.h"

struct GLFWwindow;
class Game;
class Frustum;

class Camera
{
public:
	Camera(Game* game, GLFWwindow* window);
	~Camera(void);

	void move(float dt);
	glm::mat4& getViewMatrix();
	glm::mat4& getProjectionMatrix();

	glm::vec3& getPos();
	glm::vec3& getDir();

	Frustum* getFrustum();

private:

	GLFWwindow* window;
	Game* game;
	Frustum* frustum;

	static float maxViewY;
	static float minViewY;

	static int fov;
	static int closeView;
	static int farView;

	float viewX;
	float viewY;

	float speed;
	
	float mouseLimiter;

	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

