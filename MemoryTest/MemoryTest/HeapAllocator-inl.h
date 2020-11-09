#pragma once


inline MemoryBlock* HeapAllocator::GetMemoryBlock()
{
    //assert(pFreeList != nullptr);

    MemoryBlock* pReturnBlock = pFreeMemBlocks;
    pFreeMemBlocks = pFreeMemBlocks->pNextBlock;

    return pReturnBlock;
}

inline void HeapAllocator::ReturnMemoryBlock(MemoryBlock* i_pFreeBlock)
{
    assert(i_pFreeBlock != nullptr);

    i_pFreeBlock->pBaseAddress = nullptr;
    i_pFreeBlock->BlockSize = 0;
    i_pFreeBlock->pNextBlock = pFreeMemBlocks;

    pFreeMemBlocks = i_pFreeBlock;
}

inline bool HeapAllocator::isAllocated(void* ptr)
{
    MemoryBlock* free = pFreeList;
    while (free)
    {
        if (free->pBaseAddress == ptr)
        {
            return true;
        }
        if (free->pBaseAddress == free->pNextBlock->pNextBlock->pBaseAddress)
        {
            break;
        }
        free = free->pNextBlock;
    }
    return false;
}

inline void HeapAllocator::ShowOutstandingAllocations()
{
    MemoryBlock* out = pOutstandingAllocations;
    while (out)
    {
        std::cout << out->pBaseAddress;
        std::cout << '\n';
        std::cout << out->BlockSize;
        std::cout << '\n';

        out = out->pNextBlock;
        if (out->pBaseAddress == out->pNextBlock->pNextBlock->pBaseAddress)
        {
            std::cout << out->pBaseAddress;
            std::cout << '\n';
            std::cout << out->BlockSize;
            std::cout << '\n';

            std::cout << out->pNextBlock->pBaseAddress;
            std::cout << '\n';
            std::cout << out->pNextBlock->BlockSize;
            std::cout << '\n';
            break;
        }
    }
}

inline void HeapAllocator::ShowFreeBlocks()
{
    MemoryBlock* free = pFreeList;
    while (free)
    {
        std::cout << free->pBaseAddress;
        std::cout << '\n';
        std::cout << free->BlockSize;
        std::cout << '\n';

        if (free->pNextBlock != nullptr)
        {
            free = free->pNextBlock;
            
        }
        else
        {
            break;
        }
    }
}