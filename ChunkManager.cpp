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

	chunk->generateTerrain(&mGenerator);
	chunk->createMesh(pRenderer);

	chunkList.push_back(*chunk);

/*		// Implement perlin noise
	Chunk* chunk2 = new Chunk(glm::vec3(1,0,0));

	chunk2->generateTerrain(&mGenerator);
	chunk2->createMesh(pRenderer);

	chunkList.push_back(*chunk2);

			// Implement perlin noise
	Chunk* chunk3 = new Chunk(glm::vec3(0,0,1));

	chunk3->generateTerrain(&mGenerator);
	chunk3->createMesh(pRenderer);

	chunkList.push_back(*chunk3);*/

}