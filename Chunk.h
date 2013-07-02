#pragma once

#include "Block.h"
#include "GLRenderer.h"
#include "TerrainGenerator.h";

class GLRenderer;
class Block;

class Chunk
{
public:
	Chunk(glm::vec3 pos);
	~Chunk(void);

	void update(float dt);
	void render(GLRenderer* pRenderer);

	glm::vec4 getCubeColor(int x, int y, int z);
	static const int CHUNK_SIZE = 16;
	void activateBlock(int x, int y, int z, bool active);
	void setBlockType(int x, int y, int z, BlockType type);

	void createMesh(GLRenderer* pRenderer);
	void generateTerrain(TerrainGenerator* generator);

private:
	int meshID;

	Block*** mBlocks;
	glm::vec3 mPos;

	void createCube(int x, int y, int z, GLRenderer* pRenderer);
	
};

