#include "InputManager.h"
#include <GL/glfw3.h>


InputManager::InputManager(GLFWwindow* window)
{
	this->window = window;
	init();
}


InputManager::~InputManager(void)
{

}

void InputManager::init()
{
	//glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun) mouseCallBack);

}

void InputManager::update()
{
	glfwGetCursorPos(window, &mouse_posx, &mouse_posy);
}

void InputManager::mouseCallBack(GLFWwindow* window, int button, int pressed, int modifier)
{
	if(button < 0xF)
	{
		if(pressed)
			InputManager::mouse[button] = true;
		else
			InputManager::mouse[button] = false;
	}
}

void InputManager::charCallBack(int character, int pressed)
{
	if(character < 0xFF)
	{
		if(pressed == GLFW_PRESS)
			keys[character] = true;
		else
			keys[character] = false;
	}
}

bool InputManager::keyIsPressed(char c)
{
	if(c < 0xFF)
		return keys[c];
	return false;
}

bool InputManager::mouseIsPressed(KeyButtons button)
{
	return mouse[button];
}