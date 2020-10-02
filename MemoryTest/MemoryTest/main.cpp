#include <cassert>



struct MemoryBlock
{
	size_t size;
	void* Address;
	MemoryBlock* nextMem;
};


MemoryBlock Heap{10000,nullptr,nullptr};
MemoryBlock* FreeMem = &Heap;
MemoryBlock* AllocMem = nullptr;

void* allocOne()
{
	MemoryBlock* returnBlock = FreeMem;
	FreeMem = FreeMem->nextMem;
	FreeMem->size--;
	if (AllocMem == nullptr)
	{
	}
}

MemoryBlock* FindOpenBlock()
{
	MemoryBlock* returnBlock = FreeMem;
	FreeMem = FreeMem->nextMem;
	return returnBlock;
}

void* FindOpenSize(size_t i_size)
{
	assert(FreeMem != nullptr && i_size > 0);
	MemoryBlock* freeBlock = FreeMem;
	while (freeBlock) 
	{ 
		if(freeBlock->size > i_size)
			break;
		freeBlock = freeBlock->nextMem;
	}
	assert(freeBlock);
	return freeBlock->Address;

}

void InitializeMem(void* startBlock, size_t numberOfBytes)
{
	assert(startBlock != nullptr && numberOfBytes > sizeof(MemoryBlock));

	FreeMem = reinterpret_cast<MemoryBlock*>(startBlock);

	MemoryBlock* current = FreeMem;

	const size_t numberOfBlocks = numberOfBytes / sizeof(MemoryBlock);

	for (int i = 0; i < numberOfBlocks - 1; i++, current++)
	{
		current->Address = nullptr;
		current->size = 0;
		current->nextMem = current + 1;

	}
	current->Address = nullptr;
	current->size = 0;
	current->nextMem = nullptr;

}