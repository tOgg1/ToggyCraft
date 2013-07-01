#include "GLRenderer.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glfw3.h>


GLRenderer::GLRenderer(Game* game, GLFWwindow* window)
{
	this->window = window;
	this->game = game;
	this->programID = LoadShaders("CubeVertexShader.txt", "CubeFragmentShader.txt");
	
	this->MVPHandle = glGetUniformLocation(this->programID, "MVP");
	this->modelHandle = glGetUniformLocation(this->programID, "Model");
	this->viewHandle = glGetUniformLocation(this->programID, "View");
	
	this->posHandle = glGetAttribLocation(this->programID, "vertexPosition_modelspace");
	this->colorHandle = glGetAttribLocation(this->programID, "vertexColor");
	this->normalHandle = glGetAttribLocation(this->programID, "vertexNormal_modelspace");

	FOV = 45;
	projectionMatrix = glm::perspective(FOV, float(Game::screenWidth/Game::screenHeight), 0.1f, 100.0f);
	currentID = -1;
}


GLRenderer::~GLRenderer(void)
{

}

void GLRenderer::startMesh(int* id)
{
	*id = getNextID();
	activeID = *id;
	activeMesh.translation = glm::vec3(0,0,0);
}

int GLRenderer::addPointToMesh(int id, glm::vec3 point, glm::vec4 color, glm::vec3 normal)
{
	if(id != activeID)
		return -1;
	activeMesh.vertices.push_back(point);
	activeMesh.colors.push_back(color);
	activeMesh.normals.push_back(normal);

	// return index of point
	return activeMesh.vertices.size();
}

void GLRenderer::addTriangleToMesh(int id, int id1, int id2, int id3)
{
	if(id != activeID)
		return;
	activeMesh.indices.push_back(id1);
	activeMesh.indices.push_back(id2);
	activeMesh.indices.push_back(id3);
}

void GLRenderer::finishMesh(int id)
{
	GLuint vertexBuffer, colorBuffer, normalBuffer, indexBuffer;

	glGenVertexArrays(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*activeMesh.vertices.size(), &activeMesh.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*activeMesh.colors.size(), &activeMesh.colors[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*activeMesh.normals.size(), &activeMesh.normals[0], GL_STATIC_DRAW);

	meshBuffers[activeID].vertexBuffer = vertexBuffer;
	meshBuffers[activeID].colorBuffer = colorBuffer;
	meshBuffers[activeID].normalBuffer = normalBuffer;

	activeID = -1;

	activeMesh.vertices.clear();
	activeMesh.colors.clear();
	activeMesh.normals.clear();
	activeMesh.indices.clear();
}

void GLRenderer::renderMesh(int id)
{
	glUseProgram(this->programID);
	
	glm::mat4 viewMatrix = camera->getViewMatrix();
	glm::mat4 modelMatrix = getTranslation(glm::vec3(0,0,0));
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	
	glUniformMatrix4fv(MVPHandle, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewHandle, 1, GL_FALSE, &viewMatrix[0][0]);	

	glEnableVertexAttribArray(posHandle);
	glBindBuffer(GL_ARRAY_BUFFER, meshBuffers[id].vertexBuffer);
	glVertexAttribPointer(posHandle, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	

	glEnableVertexAttribArray(colorHandle);
	glBindBuffer(GL_ARRAY_BUFFER, meshBuffers[id].colorBuffer);
	glVertexAttribPointer(colorHandle, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(normalHandle);
	glBindBuffer(GL_ARRAY_BUFFER, meshBuffers[id].normalBuffer);
	glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 24);

	glDisableVertexAttribArray(posHandle);
	glDisableVertexAttribArray(colorHandle);
	glDisableVertexAttribArray(normalHandle);
}

glm::mat4 GLRenderer::getTranslation(glm::vec3 pos)
{
	return glm::translate(glm::mat4(1.0f), pos);
}

void GLRenderer::setTranslation(glm::vec3 pos)
{
	if(activeID == -1)
		return;
	
	meshBuffers[activeID].translation = pos;
}

int GLRenderer::getNextID()
{
	return ++currentID;
}
