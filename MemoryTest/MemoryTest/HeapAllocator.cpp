#ifdef _DEBUG
#endif

#include <cassert>
#include "HeapAllocator.h"
#include <iostream>




HeapAllocator* HeapAllocator::Create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks)
{
    HeapAllocator* TheHeapAllocator = reinterpret_cast<HeapAllocator*>(i_pHeapMemory);
    i_pHeapMemory = TheHeapAllocator + 1;
    i_HeapMemorySize -= sizeof(HeapAllocator);

    return new (TheHeapAllocator) HeapAllocator(i_pHeapMemory, i_HeapMemorySize, i_NumMemBlocks);
}

HeapAllocator::HeapAllocator(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks) :
    pFreeMemBlocks(InitializeMemoryBlocks(i_pHeapMemory, i_NumMemBlocks * sizeof(MemoryBlock))),
    pFreeList(nullptr),
    pOutstandingAllocations(nullptr)
{
    pFreeList = GetMemoryBlock();
    assert(pFreeList);
    
    pFreeList->pBaseAddress = reinterpret_cast<char*>(i_pHeapMemory) + (i_NumMemBlocks * sizeof(MemoryBlock));
    pFreeList->BlockSize = i_HeapMemorySize - (i_NumMemBlocks * sizeof(MemoryBlock));
    pFreeList->pNextBlock = nullptr;
}

MemoryBlock* HeapAllocator::InitializeMemoryBlocks(void* i_pBlocksMemory, size_t i_BlocksMemorySize)
{
    assert(i_pBlocksMemory != nullptr);
    assert(i_BlocksMemorySize > sizeof(MemoryBlock));
    
  
    MemoryBlock* pCurrentBlock = reinterpret_cast<MemoryBlock*>(i_pBlocksMemory);
    const size_t numBlocks = i_BlocksMemorySize / sizeof(MemoryBlock);
     

    for( size_t i = 0; i < (numBlocks - 1); i++)
    {
        pCurrentBlock->pBaseAddress = nullptr;
        pCurrentBlock->BlockSize = 0;
        pCurrentBlock->pNextBlock = pCurrentBlock + 1;

        pCurrentBlock++;
    }

    // last block, end the list
    pCurrentBlock->pBaseAddress = nullptr;
    pCurrentBlock->BlockSize = 0;
    pCurrentBlock->pNextBlock = nullptr;

    return reinterpret_cast<MemoryBlock*>(i_pBlocksMemory);
}



void HeapAllocator::Coalesce()
{
    MemoryBlock* current = pFreeList;
    MemoryBlock* compare;
    while (current != nullptr)
    {
        compare = pFreeList;
        while (compare != nullptr)
        {
            if (reinterpret_cast<void*>(reinterpret_cast<char*>(current->pBaseAddress) + current->BlockSize) == compare->pBaseAddress)
            {
                current->BlockSize += compare->BlockSize;
                current->pNextBlock = compare->pNextBlock;
                ReturnMemoryBlock(compare);
                break;

            }

            compare = compare->pNextBlock;
            
        }
        current = current->pNextBlock;
    }
    
}

void* HeapAllocator::alloc(size_t size)
{
    if (size <= 0)
        return nullptr;

    MemoryBlock* baseBlock = GetMemoryBlock();

    MemoryBlock* free = pFreeList;
#if defined(_DEBUG)
    size += 4;
#endif
    //find a memory block in free thats large enough with alignment
    while (free)
    {
        if (free->BlockSize > size + (size%4))
            break;
        free = free->pNextBlock;
    }
    assert(free);

    //find the back of the memory block
    void* back = reinterpret_cast<void*>(reinterpret_cast<char*>(free->pBaseAddress) + size);
    //4 byte alignment
    size_t amend = 4 - (size % 4);
    if (amend == 4)
    {
        amend = 0;
    }
#if defined(_DEBUG)
    amend += 4;
#endif
    //move back from the end of the memory block
    baseBlock->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<char*>(back)-size-amend);
    baseBlock->BlockSize = size + amend;
    //track the allocated memory
    if (pOutstandingAllocations == nullptr)
    {
        pOutstandingAllocations = baseBlock;
    }
    else
    {
        baseBlock->pNextBlock = pOutstandingAllocations;
        pOutstandingAllocations = baseBlock;
    }
    //shrink the size of free
    free->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<char*>(free->pBaseAddress) + size + amend);
    free->BlockSize -= size + amend;
    //return the address
    return baseBlock->pBaseAddress;
}

void HeapAllocator::freeMem(void* ptr)
{
    if (ptr == nullptr)
        return;

    MemoryBlock* out = pOutstandingAllocations;
    if (out->pBaseAddress == ptr)
    {
        pOutstandingAllocations = out->pNextBlock;
        out->pNextBlock = pFreeList;
        pFreeList = out;
    }
    else
    {
        while (out)
        {
            if (out->pNextBlock->pBaseAddress == ptr)
            {
                break;
            }
            out = out->pNextBlock;
        }

        if (out)
        {
            MemoryBlock* temp = out->pNextBlock;
            out->pNextBlock = out->pNextBlock->pNextBlock;

            temp->pNextBlock = pFreeList;
            pFreeList = temp;
        }
        
    }
    
    Coalesce();
}

