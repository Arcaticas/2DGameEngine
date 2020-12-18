#pragma once
#include "BitArray.h"
#include <cassert>

class HeapAllocator;
class BitArray;

class FixedSizeAllocator
{
public:

	size_t fixedSize;
	size_t numberOfBlocks;
	BitArray* indexList;
	void* baseAddress;

	FixedSizeAllocator(size_t i_fixedSize, size_t i_numbOfBlocks, HeapAllocator* i_pAllocator);
	~FixedSizeAllocator();

	inline static FixedSizeAllocator* Create(size_t i_fixedSize, size_t i_numbOfBlocks,HeapAllocator* i_heapAllocator);

	void* alloc();
	void free(void* i_ptr);

	inline bool isAllocated(void* i_ptr);
	inline void ShowOutstandingAllocations();
	inline void ShowFreeBlocks();

};

#include "FixedSizeAllocator-inl.h"