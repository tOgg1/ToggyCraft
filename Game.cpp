#include "Game.h"
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
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW");
	}

	this->window = glfwCreateWindow(800, 600, "ToggyCraft", NULL, NULL);
	
	if(!this->window)
	{
		glfwTerminate();
		fprintf(stderr, "Failed to create window");
	}

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


	camera = new Camera(window);
	renderer = new GLRenderer(this, window);
	manager = new ChunkManager(renderer);
	
	manager->generateChunks();

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

		camera->move(delta);
		manager->update(delta, camera);

		glfwSwapBuffers(this->window);
		glfwPollEvents();

	} while(glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(this->window));

	this->cleanup();
}

void Game::cleanup()
{
	glfwDestroyWindow(this->window);
}
