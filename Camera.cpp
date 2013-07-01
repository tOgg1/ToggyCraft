#include "Camera.h"
#include "GLRenderer.h"
#include <algorithm>
#include <glm\gtc\matrix_transform.hpp>
#include <GL/glfw3.h>

float Camera::maxViewY = 3.14f/2;
float Camera::minViewY = -3.14f/2;

Camera::Camera(GLFWwindow* window)
{
	this->window = window;

	viewX = 3.14f;
	viewY = 0.0f;

	speed = 5.0f;

	pos = glm::vec3(0, 0, 10);
	dir = glm::vec3(
		cos(viewY)*sin(viewX),
		sin(viewY),
		cos(viewY)*cos(viewX));

	glm::vec3 right = glm::vec3(
		sin(viewX - 3.14f/2.0f),
		0,
		cos(viewX - 3.14f/2.0f));
	
	up = glm::cross(dir, right);

	viewMatrix = glm::lookAt(pos, pos+dir, right);
}


Camera::~Camera(void)
{

}

glm::mat4& Camera::getViewMatrix()
{
	return viewMatrix;
}

void Camera::move(float dt)
{
	double xPos, yPos;
	
	glfwGetCursorPos(this->window, &xPos, &yPos);
	
	viewX += dt*mouseLimiter*float(Game::screenWidth/2 - xPos);
	viewY += dt*mouseLimiter*float(Game::screenHeight/2 - yPos);

	// clamp viewY
	viewY = (viewY > maxViewY) ? maxViewY : (viewY < minViewY) ? minViewY : viewY;

	dir = glm::vec3(
		cos(viewY)*sin(viewX),
		sin(viewY),
		cos(viewY)*cos(viewX));

	glm::vec3 right = glm::vec3(
		sin(viewX - 3.14f/2.0f),
		0,
		cos(viewX - 3.14f/2.0f));

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos += dir * dt * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos -= dir * dt * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		pos -= right * dt * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		pos += right * dt * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		pos += glm::vec3(0,1,0)*dt*speed;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		pos -= glm::vec3(0,1,0)*dt*speed;
	}

	up = glm::cross(right, dir);

	viewMatrix = glm::lookAt(pos, pos + dir, up);
}
