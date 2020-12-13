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

MemoryBlock* HeapAllocator::GetMemoryBlock()
{
    
    //assert(pFreeMemBlocks != nullptr);

    if (pFreeMemBlocks == nullptr)
        return nullptr;

    MemoryBlock* pReturnBlock = pFreeMemBlocks;
    pFreeMemBlocks = pFreeMemBlocks->pNextBlock;

    return pReturnBlock;
}

void HeapAllocator::ReturnMemoryBlock( MemoryBlock* i_pFreeBlock)
{
    assert(i_pFreeBlock != nullptr);

    i_pFreeBlock->pBaseAddress = nullptr;
    i_pFreeBlock->BlockSize = 0;
    i_pFreeBlock->pNextBlock = pFreeMemBlocks;

    pFreeMemBlocks = i_pFreeBlock;
}

bool HeapAllocator::isCircular(MemoryBlock* i_pList) const
{
    MemoryBlock* pFullSpeed = i_pList;
    MemoryBlock* pHalfSpeed = i_pList;
    
    bool bMoveBoth = false;
    
    while(pFullSpeed != nullptr)
    {
        pFullSpeed = pFullSpeed->pNextBlock;

        if(pFullSpeed == pHalfSpeed)
            return true;

        if(bMoveBoth)
            pHalfSpeed = pHalfSpeed->pNextBlock;

        bMoveBoth = !bMoveBoth;
    }
    return false;
}

bool HeapAllocator::Coalesce()
{
    assert(!isCircular(pFreeList));

    if (pFreeList == nullptr)
        return true;

    MemoryBlock* current = pFreeList;
    MemoryBlock* compare;

    while (current)
    {
        compare = pFreeList;
        MemoryBlock* previous_compare = nullptr;

        while (compare != nullptr)
        {
            // does current end where compare starts?
            if (reinterpret_cast<char*>(current->pBaseAddress) + current->BlockSize == compare->pBaseAddress)
            {
                // consome compare's bytes
                current->BlockSize += compare->BlockSize;

                // now remove compare from pFreeList since it's memory is in current
                if (previous_compare)
                {
                    // if previous_comare is not null it's the compare block
                    previous_compare->pNextBlock = compare->pNextBlock;
                }
                else
                {
                    // if previous_compare is null compare is pFreeList
                    pFreeList = compare->pNextBlock;
                }

                MemoryBlock* remove = compare;
                // set it to previous because we're moving on
                compare = compare->pNextBlock;

                ReturnMemoryBlock(remove);
            }
            else
            {
                previous_compare = compare;
                compare = compare->pNextBlock;
            }
        }

        current = current->pNextBlock;
    }

    return true;
}

void* HeapAllocator::alloc(size_t size)
{
    if (size <= 0)
        return nullptr;

    MemoryBlock* baseBlock = GetMemoryBlock();

    if (baseBlock == nullptr)
        return nullptr;

    MemoryBlock* free = pFreeList;

    size_t allignmentCheck = 4 - (size % 4);
    if (allignmentCheck == 4)
        allignmentCheck = 0;


    //find a memory block in free thats large enough with alignment
    while (free)
    {
        if (free->BlockSize > size + allignmentCheck)
            break;

        free = free->pNextBlock;
    }
    
    if (free == nullptr)
        return nullptr;

    //find the back of the memory block
    void* back = reinterpret_cast<void*>(reinterpret_cast<char*>(free->pBaseAddress) + free->BlockSize);


    //move back from the end of the memory block
    baseBlock->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<char*>(back) - (size + allignmentCheck));
    baseBlock->BlockSize = size + allignmentCheck;
    baseBlock->pNextBlock = nullptr;

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
    free->BlockSize -= size + allignmentCheck;
    //return the address
    return baseBlock->pBaseAddress;
}

bool HeapAllocator::freeMem(void* ptr)
{
    if (ptr == nullptr)
        return true;

    MemoryBlock* current = pOutstandingAllocations;
    MemoryBlock* previous = nullptr;

    //Checks if first block is desired pointer
    while (current)
    {
        if (current->pBaseAddress == ptr)
        {
            // remove it from the outstanding list
            if (previous)
                previous->pNextBlock = current->pNextBlock;
            else
                pOutstandingAllocations = current->pNextBlock;
    
            // put it in the free list
            current->pNextBlock = pFreeList;
            pFreeList = current;

            break;
        }

        previous = current;
        current = current->pNextBlock;
    }

    if (current)
    {
        Coalesce();
        return true;
    }
    else
        return false;
}

bool HeapAllocator::isAllocated(void* ptr)
{
    MemoryBlock* out = pOutstandingAllocations;
    while (out)
    {
        if (out->pBaseAddress == ptr)
        {
            return true;
        }
        if (out->pNextBlock != nullptr)
            out = out->pNextBlock;
        else
            break;
    }
    return false;
}

void HeapAllocator::ShowOutstandingAllocations()
{
    if (pOutstandingAllocations)
    {
        assert(!isCircular(pOutstandingAllocations));

        MemoryBlock* out = pOutstandingAllocations;

        while (out->pNextBlock)
        {
            std::cout << out->pBaseAddress;
            std::cout << '\n';
            std::cout << out->BlockSize;
            std::cout << '\n';

            out = out->pNextBlock;
        }
    }
}

void HeapAllocator::ShowFreeBlocks()
{
    if (pFreeList)
    {
        assert(!isCircular(pFreeList));

    }
    MemoryBlock* free = pFreeList;

    while (free->pNextBlock)
    {
        std::cout << free->pBaseAddress;
        std::cout << '\n';
        std::cout << free->BlockSize;
        std::cout << '\n';

        free = free->pNextBlock;
    }
}

void HeapAllocator::Destroy()
{
    Coalesce();

    assert(pFreeList->pNextBlock == nullptr);
    assert(!pOutstandingAllocations);
}
