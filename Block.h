#pragma once

#include <glm/glm.hpp>

enum BlockType
{
	DEFAULT = 0,
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

	static const float BLOCK_SIZE;

	bool isActive();
	void setActive(bool active);

	void setBlockType(BlockType type);
	BlockType getBlockType();
	
private:
	bool mActive;
	BlockType mBlockType;
};

