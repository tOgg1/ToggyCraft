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
	float size = Chunk::CHUNK_SIZE/2;

	for(int i = 0; i < Chunk::CHUNK_SIZE; i++)
	{
		for(int j = 0; j < Chunk::CHUNK_SIZE; j++)
		{
			for(int k = 0; k < Chunk::CHUNK_SIZE; k++)
			{
				float x, y, z; x = size - i; y = size - j; z = size - k;
				if(x*x + y*y + z*z < size*size)
				{
					chunk->activateBlock(i, j, k, true);
					chunk->setBlockType(i, j, k, BlockType(j%4));
				}
			}
		}
	}
	chunk->createMesh(pRenderer);
	chunkList.push_back(*chunk);
}