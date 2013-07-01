#pragma once

#include <glm/glm.hpp>

enum BlockType
{
	DEFAULT,
	STONE,
	DIRT,
	GRASS,
	WOOD,
	SAND
};

class Block
{
public:
	Block(void);
	~Block(void);

	static const int BLOCK_SIZE = 1;

	bool isActive();
	void setActive(bool active);

	void setBlockType(BlockType type);
	BlockType getBlockType();
	
private:
	bool mActive;
	BlockType mBlockType;
};

