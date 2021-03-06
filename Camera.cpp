#include "Camera.h"
#include "GLRenderer.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glfw3.h>

float Camera::maxViewY = 3.14f/2;
float Camera::minViewY = -3.14f/2;
int Camera::fov = 70;

Camera::Camera(Game* game, GLFWwindow* window)
{
	this->window = window;
	this->game = game;
	this->frustum = new Frustum();

	viewX = 3.14f;
	viewY = 0.0f;

	speed = 3.0f;

	mouseLimiter = 1.0f;

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
	projectionMatrix = glm::perspective(float(fov), (float)Game::screenWidth/(float)Game::screenHeight, 0.1f, 200.0f);
}


Camera::~Camera(void)
{

}

glm::mat4& Camera::getViewMatrix()
{
	return viewMatrix;
}

glm::mat4& Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

glm::vec3& Camera::getPos()
{
	return pos;
}

glm::vec3& Camera::getDir()
{
	return dir;
}

void Camera::move(float dt)
{
	double xPos, yPos;
	
	xPos = game->inputManager->getMouseX();
	yPos = game->inputManager->getMouseY();
	
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

	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		speed = 30.0f;
	}

	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		speed = 10.0f;
	}

	up = glm::cross(right, dir);

	viewMatrix = glm::lookAt(pos, pos + dir, up);
	glm::mat4 mat = this->getProjectionMatrix() * this->getViewMatrix();
	frustum->setFrustum(mat);
	printf("Pos: %f %f %f dt: %f\r", pos.x, pos.y, pos.z, dt);
}

Frustum* Camera::getFrustum()
{
	return frustum;
}
