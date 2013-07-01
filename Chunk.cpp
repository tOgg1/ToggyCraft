#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos)
{
	meshID = -1;
	mPos = pos;
	mBlocks = new Block**[CHUNK_SIZE];
	for(int i = 0; i < CHUNK_SIZE; i++)
	{
		mBlocks[i] = new Block*[CHUNK_SIZE];
		for(int j = 0; j < CHUNK_SIZE; j++)
		{
			mBlocks[i][j] = new Block[CHUNK_SIZE];
		}

	}
}

Chunk::~Chunk(void)
{
	for(int i = 0; i < CHUNK_SIZE; i++)
	{
		for(int j = 0; j < CHUNK_SIZE; j++)
		{
			delete [] mBlocks[i][j];
		}
		delete [] mBlocks[i];
	}
	delete[] mBlocks;
}

glm::vec4 Chunk::getCubeColor(int x, int y, int z)
{
	// Implement some fancy coloring options
	switch(mBlocks[x][y][z].getBlockType())
	{
	default:
	case DEFAULT:
		return glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	case STONE:
		return glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	case DIRT:
		return glm::vec4(0.6f, 0.2f, 0.7f, 1.0f);
	case GRASS:
		return glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
	case WOOD:
		return glm::vec4(0.6f, 0.6f, 0.0f, 1.0f);
	case SAND:
		return glm::vec4(0.8f, 0.8f, 0.0f, 1.0f);
	
	}
}

void Chunk::update(float dt)
{
	
}

void Chunk::render(GLRenderer* pRenderer)
{
	if(meshID != -1)
	{
		pRenderer->renderMesh(meshID);
	}
}

void Chunk::createMesh(GLRenderer* pRenderer)
{
	pRenderer->startMesh(&meshID);
	pRenderer->setTranslation(mPos);

	for(int i = 0; i < CHUNK_SIZE; i++)
	{
		for(int j = 0; j < CHUNK_SIZE; j++)
		{
			for(int k = 0; k < CHUNK_SIZE; k++)
			{
				if(!mBlocks[i][j][k].isActive())
				{
					continue;
				}
				createCube(i, j, k, pRenderer);
			}
		}
	}
	pRenderer->finishMesh(meshID);
}

void Chunk::createCube(int x, int y, int z, GLRenderer* pRenderer)
{
	glm::vec3 p1, p2, p3, p4, p5, p6, p7, p8, n1, n2, n3, n4, n5, n6;	

	// Cube points
	p1 = glm::vec3(x - Block::BLOCK_SIZE, y - Block::BLOCK_SIZE, z + Block::BLOCK_SIZE);
	p2 = glm::vec3(x + Block::BLOCK_SIZE, y - Block::BLOCK_SIZE, z + Block::BLOCK_SIZE);
	p3 = glm::vec3(x + Block::BLOCK_SIZE, y + Block::BLOCK_SIZE, z + Block::BLOCK_SIZE);
	p4 = glm::vec3(x - Block::BLOCK_SIZE, y + Block::BLOCK_SIZE, z + Block::BLOCK_SIZE);
	p5 = glm::vec3(x + Block::BLOCK_SIZE, y - Block::BLOCK_SIZE, z - Block::BLOCK_SIZE);
	p6 = glm::vec3(x - Block::BLOCK_SIZE, y - Block::BLOCK_SIZE, z - Block::BLOCK_SIZE);
	p7 = glm::vec3(x - Block::BLOCK_SIZE, y + Block::BLOCK_SIZE, z - Block::BLOCK_SIZE);
	p8 = glm::vec3(x + Block::BLOCK_SIZE, y + Block::BLOCK_SIZE, z - Block::BLOCK_SIZE);

	// Cube Normals (front, back, right, left, top, bottom)
	n1 = glm::vec3(0.0f, 0.0f, 1.0f);
	n2 = glm::vec3(0.0f, 0.0f, -1.0f);
	n3 = glm::vec3(1.0f, 0.0f, 0.0f);
	n4 = glm::vec3(-1.0f, 0.0f, 0.0f);
	n5 = glm::vec3(0.0f, 1.0f, 0.0f);
	n6 = glm::vec3(0.0f, -1.0f, 0.0f);

	glm::vec4 color = getCubeColor(x, y, z);

	// Internal Mesh-ID's of points
	unsigned int id1, id2, id3, id4, id5, id6, id7, id8;

	// orders points in triangles and adds normals

	// Front face

	id1 = pRenderer->addPointToMesh(meshID, p1, color, n1);
	id2 = pRenderer->addPointToMesh(meshID, p2, color, n1);
	id3 = pRenderer->addPointToMesh(meshID, p3, color, n1);
	id4 = pRenderer->addPointToMesh(meshID, p4, color, n1);

	pRenderer->addTriangleToMesh(meshID, id1, id2, id3); 
	pRenderer->addTriangleToMesh(meshID, id1, id3, id4);

	// Back face
	id5 = pRenderer->addPointToMesh(meshID, p5, color, n2);
	id6 = pRenderer->addPointToMesh(meshID, p6, color, n2);
	id7 = pRenderer->addPointToMesh(meshID, p7, color, n2);
	id8 = pRenderer->addPointToMesh(meshID, p8, color, n2);

	pRenderer->addTriangleToMesh(meshID, id5, id6, id7);
	pRenderer->addTriangleToMesh(meshID, id5, id7, id8);

	// Right face
	id2 = pRenderer->addPointToMesh(meshID, p2, color, n3);
	id5 = pRenderer->addPointToMesh(meshID, p5, color, n3);
	id8 = pRenderer->addPointToMesh(meshID, p8, color, n3);
	id3 = pRenderer->addPointToMesh(meshID, p3, color, n3);

	pRenderer->addTriangleToMesh(meshID, id2, id5, id8);
	pRenderer->addTriangleToMesh(meshID, id2, id8, id3);
	
	// Left face
	id6 = pRenderer->addPointToMesh(meshID, p6, color, n4);
	id1 = pRenderer->addPointToMesh(meshID, p1, color, n4);
	id4 = pRenderer->addPointToMesh(meshID, p4, color, n4);
	id7 = pRenderer->addPointToMesh(meshID, p7, color, n4);

	pRenderer->addTriangleToMesh(meshID, id6, id1, id4);
	pRenderer->addTriangleToMesh(meshID, id6, id4, id7);

	// Top face
	id4 = pRenderer->addPointToMesh(meshID, p4, color, n5);
	id3 = pRenderer->addPointToMesh(meshID, p3, color, n5);
	id8 = pRenderer->addPointToMesh(meshID, p8, color, n5);
	id7 = pRenderer->addPointToMesh(meshID, p7, color, n5);

	pRenderer->addTriangleToMesh(meshID, id4, id3, id8);
	pRenderer->addTriangleToMesh(meshID, id4, id8, id7);
	
	// Bottom face
	id1 = pRenderer->addPointToMesh(meshID, p1, color, n6);
	id2 = pRenderer->addPointToMesh(meshID, p2, color, n6);
	id5 = pRenderer->addPointToMesh(meshID, p5, color, n6);
	id6 = pRenderer->addPointToMesh(meshID, p6, color, n6);

	pRenderer->addTriangleToMesh(meshID, id1, id2, id5);
	pRenderer->addTriangleToMesh(meshID, id1, id5, id6);

}

void Chunk::activateBlock(int x, int y, int z, bool active)
{
	mBlocks[x][y][z].setActive(active);
}


void Chunk::setBlockType(int x, int y, int z, BlockType type)
{
	mBlocks[x][y][z].setBlockType(type);
}