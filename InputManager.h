#pragma once

enum KeyButtons
{
	LEFT = 0,
	RIGHT,
	MIDDLE,
	MISC_1,
	MISC_2,
	MISC_3,
	MISC_4,
	MISC_5,
	MISC_6,
	MISC_7,
	MISC_8
};

class GLFWwindow;

class InputManager
{
public:
	InputManager(GLFWwindow* window);
	~InputManager(void);

	void init();
	void update();
	void mouseCallBack(GLFWwindow* window, int button, int pressed, int modifier);
	void charCallBack(int character, int pressed);

	bool keyIsPressed(char c);
	bool mouseIsPressed(KeyButtons button);

	void getMousePos(double* posx, double* posy);

private:
	GLFWwindow* window;

	double mouse_posx, mouse_posy;
	
	bool keys[0xFF];
	bool mouse[0xF];
};

