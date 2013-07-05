#pragma once
#include <vector>
#include "Camera.h"
#include "Chunk.h"
#include "GLRenderer.h"
#include "TerrainGenerator.h"

class GLRenderer;
class Chunk;

class ChunkManager
{
public:
	ChunkManager(GLRenderer* renderer);
	~ChunkManager(void);
	
	void update(float dt, Camera* camera);
	void generateChunks();
	void getChunkCoordinates(float x, float y, float z, int* sx, int* sy, int* sz);

	static int CHUNK_LOAD_PER_FRAME;
	static int CHUNK_REBUILD_PER_FRAME;
	static int ACTIVE_CHUNKS_SIZE;

	TerrainGenerator* getTerrainGenerator();
	GLRenderer* getRenderer();

	Chunk* getChunk(int x, int y, int z);
	Block* getBlock(int x, int y, int z);

private:
	GLRenderer* pRenderer;
	TerrainGenerator* mGenerator;

	int low_x, low_y, low_z;
	int chunkVisibility;

	glm::vec3 lastCameraPos, lastCameraDir;

	void loadChunks();
	void setupChunks();
	void rebuildChunks();
	void unloadChunks();
	void updateVisibleChunks(Camera* camera);
	void updateRenderList();
	void renderChunks();
	

	std::vector<Chunk*> chunkList;
	std::vector<Chunk*> renderFlagList;
	std::vector<Chunk*> visibilityList;
	std::vector<Chunk*> renderList;
	std::vector<Chunk*> unloadList;
	std::vector<Chunk*> loadList;
	std::vector<Chunk*> setupList;
	std::vector<Chunk*> rebuildList;
};

