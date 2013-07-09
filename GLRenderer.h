#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Game.h"
#include "Camera.h"
#include "Chunk.h"

#include <map>
#include <vector>

class Game;
class Camera;
class Chunk;

struct Mesh
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
	glm::vec3 translation;
};

struct MeshBuffer
{
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;
	int indexSize;
	glm::vec3 translation;
};

class GLRenderer
{
public:
	GLRenderer(Game* game, GLFWwindow* window, Camera* camera);
	~GLRenderer(void);

	void update();

	void startMesh(int* id);
	void finishMesh(int id, Chunk* chunk);

	int addPointToMesh(int id, glm::vec3 &point, glm::vec4 &color, glm::vec3 &normal);
	void addTriangleToMesh(int id, int point1, int point2, int point3);
	
	void renderACube();
	void renderMesh(int id);

	bool chunkInFrustum(Chunk* chunk);
	bool pointInFrustum(glm::vec3 &pos);
	bool sphereInFrustum(glm::vec3 &center, double radius);

	void setTranslation(glm::vec3 pos);

	glm::mat4 getTranslation(glm::vec3 pos);

	int getNextID();

private:
	GLuint programID;
	GLuint posHandle;
	GLuint colorHandle;
	GLuint normalHandle;

	GLuint MVPHandle;
	GLuint modelHandle;
	GLuint viewHandle;

	GLFWwindow* window;
	Game* game;
	Camera* camera;

	int currentID;
	int activeID;
	int lockValue;

	Mesh activeMesh;
	std::map<unsigned int, MeshBuffer> meshBuffers;
};

