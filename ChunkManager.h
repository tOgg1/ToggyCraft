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

private:
	GLRenderer* pRenderer;
	TerrainGenerator mGenerator;

	std::vector<Chunk> chunkList;
	std::vector<Chunk> renderList;
	std::vector<Chunk> loadList;
	std::vector<Chunk> rebuildList;
};

