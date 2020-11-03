#pragma once
#include <iostream>
#include <cassert>
struct  MemoryBlock
{
    void* pBaseAddress;
    size_t BlockSize;
    MemoryBlock* pNextBlock;
};



class HeapAllocator
{
public:
    static HeapAllocator* Create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks);
    void* alloc(size_t size);
    void freeMem(void* ptr);
    inline bool isAllocated(void* ptr);

    inline void ShowOutstandingAllocations();
    inline void ShowFreeBlocks();

private:
    HeapAllocator(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks);

    MemoryBlock* InitializeMemoryBlocks(void* i_pBlocksMemory, size_t i_BlocksMemorySize);
    inline MemoryBlock* GetMemoryBlock();
    inline void ReturnMemoryBlock(MemoryBlock* i_pFreeBlock);
    void Coalesce();

    struct MemoryBlock* pFreeMemBlocks;
    struct MemoryBlock* pFreeList;
    struct MemoryBlock* pOutstandingAllocations;
};

#include "HeapAllocator-inl.h"