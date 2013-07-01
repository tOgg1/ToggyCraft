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
			if(i*i + j*j < Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE)
			{
				chunk->activateBlock(i, j, 0, true);
				chunk->setBlockType(i, j, 0, GRASS);
			}
		}
	}
	chunk->createMesh(pRenderer);
	chunkList.push_back(*chunk);
}