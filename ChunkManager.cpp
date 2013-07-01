#include "ChunkManager.h"


ChunkManager::ChunkManager(GLRenderer* renderer)
{
	pRenderer = renderer;
}


ChunkManager::~ChunkManager(void)
{
	
}

void ChunkManager::update(float dt, Camera* camera)
{
	// Do fancy updating

	std::vector<Chunk>::iterator it;

	for(it = chunkList.begin(); it != chunkList.end(); ++it)
	{
		it->render(pRenderer);
	}
}

void ChunkManager::generateChunks()
{
	// Implement perlin noise
	Chunk* chunk = new Chunk(glm::vec3(0,0,0));
	for(int i = 0; i < Chunk::CHUNK_SIZE; i++)
	{
		for(int j = 0; j < Chunk::CHUNK_SIZE; j++)
		{
			int x, y; x = Chunk::CHUNK_SIZE/2 - i; y = Chunk::CHUNK_SIZE/2 - j;
			if(x*x + y*y < Chunk::CHUNK_SIZE)
			{
				chunk->activateBlock(i, 0, j, true);
				chunk->setBlockType(i, 0, j, GRASS);
			}
		}
	}
	chunk->createMesh(pRenderer);
	chunkList.push_back(*chunk);
}