#include "InputManager.h"


InputManager::InputManager(GLFWwindow* window)
{
	this->window = window;
}

InputManager::~InputManager(void)
{

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
			mouse[button] = true;
		else
			mouse[button] = false;
	}
}

void InputManager::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int modifier)
{
	if(key < 350)
	{
		if(action == GLFW_PRESS)
			keys[key] = true;
		else
			keys[key] = false;
	}
}

bool InputManager::keyIsPressed(char c)
{
	if(c < 0xFF)
		return keys[c];
	return false;
}

bool InputManager::mouseIsPressed(int button)
{
	return mouse[button];
}

void InputManager::getMousePos(double* posx, double* posy)
{
	*posx = mouse_posx;
	*posy = mouse_posy;
}


double InputManager::getMouseX()
{
	return mouse_posx;
}

double InputManager::getMouseY()
{
	return mouse_posy;
}

