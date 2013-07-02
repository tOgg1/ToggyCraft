#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class Camera
{
public:
	Camera(GLFWwindow* window);
	~Camera(void);

	void move(float dt);
	glm::mat4& getViewMatrix();
	glm::mat4& getProjectionMatrix();

private:

	GLFWwindow* window;

	static float maxViewY;
	static float minViewY;

	static int fov;

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

