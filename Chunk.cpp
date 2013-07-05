#include "Chunk.h"

Chunk::Chunk(ChunkManager* manager, glm::vec3 pos)
{
	mChunkManager = manager;
	meshID = -1;
	mPos = pos;
	mBlocks = new Block**[CHUNK_SIZE];
	mLoaded = false;
	mSetup = false;
	renderFlag = true;
}

Chunk::~Chunk(void)
{

}

glm::vec3 Chunk::getPos()
{
	return mPos;
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
		return glm::vec4(0.5f, 0.3f, 0.0f, 1.0f);
	case GRASS:
		return glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
	case WOOD:
		return glm::vec4(0.6f, 0.6f, 0.0f, 1.0f);
	case SAND:
		return glm::vec4(0.8f, 0.8f, 0.0f, 1.0f);
	
	}
}

void Chunk::setup()
{
	if(mSetup)
		return;
	this->createMesh(mChunkManager->getRenderer());
}

void Chunk::load()
{
	// create map-loader
	if(mLoaded)
		return;

	for(int i = 0; i < CHUNK_SIZE; i++)
	{
		mBlocks[i] = new Block*[CHUNK_SIZE];
		for(int j = 0; j < CHUNK_SIZE; j++)
		{
			mBlocks[i][j] = new Block[CHUNK_SIZE];
		}
	}

	mLoaded = true;
}

void Chunk::unload()
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

bool Chunk::isLoaded()
{
	return mLoaded;
}

bool Chunk::isSetup()
{
	return mSetup;
}

void Chunk::update(float dt)
{
	
}

void Chunk::render(GLRenderer* pRenderer)
{
	if(meshID != -1 && renderFlag == true)
	{
		pRenderer->renderMesh(meshID);
	}
}

void Chunk::createMesh(GLRenderer* pRenderer)
{
	pRenderer->startMesh(&meshID);
	pRenderer->setTranslation(glm::vec3(mPos.x*16, mPos.y*16, mPos.z*16));

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
	pRenderer->finishMesh(meshID, this);
}

void Chunk::createCube(int x, int y, int z, GLRenderer* pRenderer)
{
	// Do face-checks
	Block* x0 = getBlock(x-1, y  , z  );
	Block* x1 = getBlock(x+1, y  , z  );
	Block* y0 = getBlock(x  , y-1, z  );
	Block* y1 = getBlock(x  , y+1, z  );
	Block* z0 = getBlock(x  , y  , z-1);
	Block* z1 = getBlock(x  , y  , z+1);

	bool renderTop = y1 == NULL ? true : !y1->isActive();
	bool renderBottom = y0 == NULL ? true : !y0->isActive();
	bool renderFront = z1 == NULL ? true : !z1->isActive();
	bool renderBack = z0 == NULL ? true : !z0->isActive();
	bool renderLeft = x0 == NULL ? true : !x0->isActive();
	bool renderRight = x1 == NULL ? true : !x1->isActive();

	glm::vec3 p1, p2, p3, p4, p5, p6, p7, p8, n1, n2, n3, n4, n5, n6;	

	float blockSize = Block::BLOCK_SIZE;

	// Cube points
	p1 = glm::vec3(2*x*blockSize - blockSize, 2*y*blockSize - blockSize, 2*z*blockSize + blockSize);
	p2 = glm::vec3(2*x*blockSize + blockSize, 2*y*blockSize - blockSize, 2*z*blockSize + blockSize);
	p3 = glm::vec3(2*x*blockSize + blockSize, 2*y*blockSize + blockSize, 2*z*blockSize + blockSize);
	p4 = glm::vec3(2*x*blockSize - blockSize, 2*y*blockSize + blockSize, 2*z*blockSize + blockSize);
	p5 = glm::vec3(2*x*blockSize + blockSize, 2*y*blockSize - blockSize, 2*z*blockSize - blockSize);
	p6 = glm::vec3(2*x*blockSize - blockSize, 2*y*blockSize - blockSize, 2*z*blockSize - blockSize);
	p7 = glm::vec3(2*x*blockSize - blockSize, 2*y*blockSize + blockSize, 2*z*blockSize - blockSize);
	p8 = glm::vec3(2*x*blockSize + blockSize, 2*y*blockSize + blockSize, 2*z*blockSize - blockSize);

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
	if(renderFront)
	{
		id1 = pRenderer->addPointToMesh(meshID, p1, color, n1);
		id2 = pRenderer->addPointToMesh(meshID, p2, color, n1);
		id3 = pRenderer->addPointToMesh(meshID, p3, color, n1);
		id4 = pRenderer->addPointToMesh(meshID, p4, color, n1);

		pRenderer->addTriangleToMesh(meshID, id1, id2, id3); 
		pRenderer->addTriangleToMesh(meshID, id1, id3, id4);
	}

	if(renderBack)
	{
		// Back face
		id5 = pRenderer->addPointToMesh(meshID, p5, color, n2);
		id6 = pRenderer->addPointToMesh(meshID, p6, color, n2);
		id7 = pRenderer->addPointToMesh(meshID, p7, color, n2);
		id8 = pRenderer->addPointToMesh(meshID, p8, color, n2);

		pRenderer->addTriangleToMesh(meshID, id5, id6, id7);
		pRenderer->addTriangleToMesh(meshID, id5, id7, id8);
	}

	if(renderRight)
	{

		// Right face
		id2 = pRenderer->addPointToMesh(meshID, p2, color, n3);
		id5 = pRenderer->addPointToMesh(meshID, p5, color, n3);
		id8 = pRenderer->addPointToMesh(meshID, p8, color, n3);
		id3 = pRenderer->addPointToMesh(meshID, p3, color, n3);

		pRenderer->addTriangleToMesh(meshID, id2, id5, id8);
		pRenderer->addTriangleToMesh(meshID, id2, id8, id3);
	}
	
	if(renderLeft)
	{
		// Left face
		id6 = pRenderer->addPointToMesh(meshID, p6, color, n4);
		id1 = pRenderer->addPointToMesh(meshID, p1, color, n4);
		id4 = pRenderer->addPointToMesh(meshID, p4, color, n4);
		id7 = pRenderer->addPointToMesh(meshID, p7, color, n4);

		pRenderer->addTriangleToMesh(meshID, id6, id1, id4);
		pRenderer->addTriangleToMesh(meshID, id6, id4, id7);
	}

	if(renderTop)
	{
		// Top face
		id4 = pRenderer->addPointToMesh(meshID, p4, color, n5);
		id3 = pRenderer->addPointToMesh(meshID, p3, color, n5);
		id8 = pRenderer->addPointToMesh(meshID, p8, color, n5);
		id7 = pRenderer->addPointToMesh(meshID, p7, color, n5);

		pRenderer->addTriangleToMesh(meshID, id4, id3, id8);
		pRenderer->addTriangleToMesh(meshID, id4, id8, id7);
	}

	if(renderBottom)
	{
	
		// Bottom face
		id6 = pRenderer->addPointToMesh(meshID, p6, color, n6);
		id5 = pRenderer->addPointToMesh(meshID, p5, color, n6);
		id2 = pRenderer->addPointToMesh(meshID, p2, color, n6);
		id1 = pRenderer->addPointToMesh(meshID, p1, color, n6);

		pRenderer->addTriangleToMesh(meshID, id6, id5, id2);
		pRenderer->addTriangleToMesh(meshID, id6, id2, id1);
	}

}

void Chunk::generateTerrain(TerrainGenerator* generator)
{
	for(int x = 0; x < Chunk::CHUNK_SIZE; x++)
	{
		for(int z = 0; z < Chunk::CHUNK_SIZE; z++)
		{
			double height = generator->getHeightValue(this->mPos.x*16 + x, this->mPos.z*16 + z)*(CHUNK_SIZE-1);
			for(int y = 0; y <= (int)height; y++)
			{
				mBlocks[x][y][z].setActive(true);
				mBlocks[x][y][z].setBlockType(y > height - 2 ? GRASS : y < height - 5 ? STONE : DIRT);
			}
		}
	}
}

Block* Chunk::getBlock(int x, int y, int z)
{
	int size = CHUNK_SIZE;
	if(x > size-1 || y > size-1 || z > size-1 || x < 0 || y < 0 || z <0)
		return mChunkManager->getBlock(x + mPos.x*size, y + mPos.y*size, z + mPos.z*size);
	return &mBlocks[x][y][z];
}

bool Chunk::isFlaggedForRender()
{
	return renderFlag;
}

void Chunk::flagRender(bool flag)
{
	renderFlag = flag;
}

void Chunk::activateBlock(int x, int y, int z, bool active)
{
	mBlocks[x][y][z].setActive(active);
}

void Chunk::setBlockType(int x, int y, int z, BlockType type)
{
	mBlocks[x][y][z].setBlockType(type);
}