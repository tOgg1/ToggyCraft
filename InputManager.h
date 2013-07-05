#pragma once
#include <GL/glfw3.h>

class InputManager
{
public:
	InputManager(GLFWwindow* window);
	~InputManager(void);

	void init();
	void update();

	void mouseCallBack(GLFWwindow* window, int button, int pressed, int modifier);
	void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int modifier);

	bool keyIsPressed(char c);
	bool mouseIsPressed(int button);

	void getMousePos(double* posx, double* posy);
	double getMouseX();
	double getMouseY();

private:
	GLFWwindow* window;

	double mouse_posx, mouse_posy;
	
	bool keys[350];
	bool mouse[0xF];
};

