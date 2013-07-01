#pragma once
#include <GL/glew.h>

#include <GL/glfw3.h>
#include "GLRenderer.h"
#include "ChunkManager.h"
#include "Camera.h"

// Include GLM
#include <glm/glm.hpp>

class GLRenderer;
class Camera;
class ChunkManager;

class Game
{
	public:

		GLFWwindow* window;
		GLRenderer* renderer;
		Camera* camera;
		ChunkManager* manager;

		Game(void);
		~Game(void);

		void start();
		void run();

		static const int screenWidth = 800, screenHeight = 600;

	private:
		void cleanup();
		void initGL();
};

