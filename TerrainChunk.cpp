#include "TerrainChunk.h"

int floorFast(float x)
{
	return x == 0 ? 0 : x > 0 ? (int)x : (int)x-1;
}

TerrainChunk::TerrainChunk(ChunkManager* manager)
{
	mChunkManager = manager;
	addCount = 0;
}


TerrainChunk::~TerrainChunk(void)
{

}

void TerrainChunk::setColumn(std::vector<Chunk*> chunks)
{
	if(chunks.size() != TERRAIN_MAX_HEIGHT)
		return;

	for(int i = 0; i < TERRAIN_MAX_HEIGHT; i++)
	{
		this->chunks.push_back(chunks[i]);
	}
}

void TerrainChunk::generateTerrain(TerrainGenerator* generator)
{
	int posx = (int)chunks[0]->getPos().x;
	int posz = (int)chunks[0]->getPos().z;

	for(int x = 0; x < Chunk::CHUNK_SIZE; x++)
	{
		for(int z = 0; z < Chunk::CHUNK_SIZE; z++)
		{
			double height = generator->getHeightValue(posx*Chunk::CHUNK_SIZE + x, posz*Chunk::CHUNK_SIZE + z)*(Chunk::CHUNK_SIZE*TERRAIN_MAX_HEIGHT -1) ;
			for(int y = 0; y < Chunk::CHUNK_SIZE*TERRAIN_MAX_HEIGHT; y++)
			{
				if(height > y)
				{
					Block* block = getBlock(x,y,z);
					block->setActive(true);
					block->setBlockType(GRASS);
				}
			}
		}
	}
}

bool TerrainChunk::containsChunk(Chunk* chunk)
{
	return true;
}

Block* TerrainChunk::getBlock(int x, int y, int z)
{
	if(y > TERRAIN_MAX_HEIGHT*Chunk::CHUNK_SIZE-1 || x > Chunk::CHUNK_SIZE-1 || z > Chunk::CHUNK_SIZE-1 || x < 0 || y < 0 || z < 0)
		return NULL;

	float y_chunk = (int)float(y)/Chunk::CHUNK_SIZE;
	float y_chunkIndex = y - y_chunk*Chunk::CHUNK_SIZE;
	return chunks[y_chunk]->getBlock(x,y_chunkIndex, z);
}




