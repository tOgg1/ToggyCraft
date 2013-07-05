#pragma once
#include <GL/glew.h>

#include <GL/glfw3.h>
#include "GLRenderer.h"
#include "ChunkManager.h"
#include "Camera.h"
#include "InputManager.h"

// Include GLM
#include <glm/glm.hpp>

class GLRenderer;
class Camera;
class ChunkManager;
class InputManager;

class Game
{
	public:

		GLFWwindow* window;
		GLRenderer* renderer;
		Camera* camera;
		ChunkManager* manager;
		InputManager* inputManager;

		Game(void);
		~Game(void);

		void start();
		void run();

		static const int screenWidth = 1040, screenHeight = 585;

	private:
		void cleanup();
		void initGL();

		static Game *windowGetGame(GLFWwindow *window)
		{
			return static_cast<Game *>(glfwGetWindowUserPointer(window));
		}

		static void keyCallBackWrapper(GLFWwindow* window, int key, int scancode, int action, int modifier);
		static void mouseCallBackWrapper(GLFWwindow* window, int button, int pressed, int modifier);
};
