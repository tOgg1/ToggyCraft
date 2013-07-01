#include "Block.h"


Block::Block()
{
	mActive = false;
	mBlockType = DEFAULT;
}

Block::~Block(void)
{

}

void Block::setBlockType(BlockType type)
{
	mBlockType = type;
}

void Block::setActive(bool active)
{
	this->mActive = active;
}

bool Block::isActive()
{
	return mActive;
}

BlockType Block::getBlockType()
{
	return mBlockType;
}
