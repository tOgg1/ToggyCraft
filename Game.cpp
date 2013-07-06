#include "Game.h"
#include "Shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>

#include <GL/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLFW_DLL

Game::Game(void)
{
	
}


Game::~Game(void)
{

}

void Game::start()
{
	initGL();
	float time1 = glfwGetTime();

	camera = new Camera(this, window);
	renderer = new GLRenderer(this, window, camera);
	manager = new ChunkManager(renderer);
	inputManager = new InputManager(window);

	glfwSetMouseButtonCallback(window, &mouseCallBackWrapper);
	glfwSetKeyCallback(window, &keyCallBackWrapper);
	float time2 = glfwGetTime();

	Chunk* chunk = new Chunk(manager, glm::vec3(0,0,0));
	chunk->load();
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			for(int k = 0; k < 16; k++)
			{
				chunk->activateBlock(i,j,k,true);
			}
		}
	}

	glfwShowWindow(this->window);

	this->run();
}

void Game::run()
{
	printf("\nRunning");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	double lastTime, curTime;
	float delta;

	lastTime = glfwGetTime();
	do 
	{
		curTime = glfwGetTime();
		delta = float(curTime - lastTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		inputManager->update();
		camera->move(delta);
		glfwSetCursorPos(window, Game::screenWidth/2, Game::screenHeight/2);

		//renderer->renderACube();
		manager->update(delta, camera);

		glfwSwapBuffers(this->window);
		glfwPollEvents();
		lastTime = curTime;

	} while(glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(this->window));

	this->cleanup();
}

void Game::initGL()
{
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW");
	}

	this->window = glfwCreateWindow(screenWidth, screenHeight, "ToggyCraft", NULL, NULL);
	glfwHideWindow(this->window);
	
	if(!this->window)
	{
		glfwTerminate();
		fprintf(stderr, "Failed to create window");
	}

	glfwSetWindowUserPointer(window, this);

	glfwMakeContextCurrent(this->window);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

void Game::cleanup()
{	
	delete camera;
	delete renderer;
	delete manager;
	glfwDestroyWindow(this->window);
}

void Game::mouseCallBackWrapper(GLFWwindow* window, int button, int pressed, int modifier)
{
	windowGetGame(window)->inputManager->mouseCallBack(window, button, pressed, modifier);
}

void Game::keyCallBackWrapper(GLFWwindow* window, int key, int scancode, int action, int modifier)
{
	windowGetGame(window)->inputManager->keyCallBack(window, key, scancode, action, modifier);
}
