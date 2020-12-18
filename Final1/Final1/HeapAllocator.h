#pragma once
#include <cassert>
#include <iostream>

struct  MemoryBlock
{
    void* pBaseAddress;
    size_t BlockSize;
    MemoryBlock* pNextBlock;
};



class HeapAllocator
{
public:
    inline static HeapAllocator* Create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks);
    void* alloc(size_t size);
    bool Coalesce();
    bool freeMem(void* ptr);

    inline bool isAllocated(void* ptr);
    inline void ShowOutstandingAllocations();
    void ShowFreeBlocks();

    void Destroy();

private:
    HeapAllocator(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks);

    MemoryBlock* InitializeMemoryBlocks(void* i_pBlocksMemory, size_t i_BlocksMemorySize);
    inline MemoryBlock* GetMemoryBlock();
    inline void ReturnMemoryBlock(MemoryBlock* i_pFreeBlock);
    bool isCircular(MemoryBlock* i_pList) const;

    struct MemoryBlock* pFreeMemBlocks;
    struct MemoryBlock* pFreeList;
    struct MemoryBlock* pOutstandingAllocations;
};


#include "HeapAllocator-inl.h"
