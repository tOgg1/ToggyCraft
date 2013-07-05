#include "GLRenderer.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glfw3.h>


GLRenderer::GLRenderer(Game* game, GLFWwindow* window, Camera* camera)
{
	this->window = window;
	this->game = game;
	this->camera = camera;
	this->programID = LoadShaders("CubeVertexShader.txt", "CubeFragmentShader.txt");
	
	this->MVPHandle = glGetUniformLocation(this->programID, "MVP");
	this->modelHandle = glGetUniformLocation(this->programID, "Model");
	this->viewHandle = glGetUniformLocation(this->programID, "View");
	
	this->posHandle = glGetAttribLocation(this->programID, "vertexPosition_modelspace");
	this->colorHandle = glGetAttribLocation(this->programID, "vertexColor");
	this->normalHandle = glGetAttribLocation(this->programID, "vertexNormal_modelspace");

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
	return activeMesh.vertices.size() - 1;
}

void GLRenderer::addTriangleToMesh(int id, int id1, int id2, int id3)
{
	//if(id != activeID)
	//	return;
	activeMesh.indices.push_back(id1);
	activeMesh.indices.push_back(id2);
	activeMesh.indices.push_back(id3);
}

void GLRenderer::finishMesh(int id, Chunk* chunk)
{
	GLuint vertexBuffer, colorBuffer, normalBuffer, indexBuffer;
	
	// No vertices were added to the mesh for finalization, disregard mesh
	if(activeMesh.vertices.size() == 0)
	{
		activeID--;
		chunk->flagRender(false);
		return;
	}

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*activeMesh.vertices.size(), &activeMesh.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*activeMesh.colors.size(), &activeMesh.colors[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*activeMesh.normals.size(), &activeMesh.normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*activeMesh.indices.size(), &activeMesh.indices[0], GL_STATIC_DRAW);

	meshBuffers[activeID].vertexBuffer = vertexBuffer;
	meshBuffers[activeID].colorBuffer = colorBuffer;
	meshBuffers[activeID].normalBuffer = normalBuffer;
	meshBuffers[activeID].indexBuffer = indexBuffer;
	meshBuffers[activeID].indexSize = activeMesh.indices.size();

	activeID = -1;

	activeMesh.vertices.clear();
	activeMesh.colors.clear();
	activeMesh.normals.clear();
	activeMesh.indices.clear();
}

void GLRenderer::renderACube()
{
	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        // Right face
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,

        // Back face
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        // Left face
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,

        // Top face
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,

        // Bottom face
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
	};

	// One color for each vertex. They were generated randomly.
	static const GLfloat g_color_buffer_data[] = { 
		1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        // Right face (green)
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        // Back face (blue)
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        // Left face (yellow)
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        // Top face (cyan)
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        // Bottom face (magenta)
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f
	};

	static const GLfloat g_normal_buffer_data[] = { 
		    0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            // Right face
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            // Back face
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

            // Left face
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,

            // Top face
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            // Bottom face
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	GLuint normalBuffer;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_normal_buffer_data), g_normal_buffer_data, GL_STATIC_DRAW);

	glUseProgram(this->programID);

	glm::mat4 viewMatrix = camera->getViewMatrix();
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 MVP = camera->getProjectionMatrix() * viewMatrix * modelMatrix;

	glUniformMatrix4fv(MVPHandle, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewHandle, 1, GL_FALSE, &viewMatrix[0][0]);	

	glEnableVertexAttribArray(posHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(posHandle, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	

	glEnableVertexAttribArray(colorHandle);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(colorHandle, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(normalHandle);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(posHandle);
	glDisableVertexAttribArray(colorHandle);
	glDisableVertexAttribArray(normalHandle);
}

void GLRenderer::renderMesh(int id)
{
	glUseProgram(this->programID);
	
	glm::mat4 viewMatrix = camera->getViewMatrix();
	glm::mat4 projectionMatrix = camera->getProjectionMatrix();
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), meshBuffers[id].translation);
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffers[id].indexBuffer);

	glDrawElements(GL_TRIANGLES, meshBuffers[id].indexSize, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(posHandle);
	glDisableVertexAttribArray(colorHandle);
	glDisableVertexAttribArray(normalHandle);
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
