#pragma once

#include "Block.h"
#include "GLRenderer.h"
#include "TerrainGenerator.h"

class TerrainGenerator;
class ChunkManager;
class GLRenderer;
class Block;

class Chunk
{
public:
	Chunk(ChunkManager* manager, glm::vec3 pos);
	~Chunk(void);

	static const int CHUNK_SIZE = 16;

	void update(float dt);
	void render(GLRenderer* pRenderer);

	void load();
	void unload();
	void setup();

	bool isLoaded();
	bool isSetup();

	glm::vec4 getCubeColor(int x, int y, int z);
	glm::vec3 getPos();

	Block* getBlock(int x, int y, int z);

	void activateBlock(int x, int y, int z, bool active);
	void setBlockType(int x, int y, int z, BlockType type);

	void createMesh(GLRenderer* pRenderer);
	void generateTerrain(TerrainGenerator* generator);

	bool flaggedForRender();

private:
	ChunkManager* mChunkManager;

	int meshID;
	bool mLoaded;
	bool mSetup;
	bool renderFlag;

	Block*** mBlocks;
	glm::vec3 mPos;

	void createCube(int x, int y, int z, GLRenderer* pRenderer);
	
};

