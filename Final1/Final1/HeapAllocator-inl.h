#pragma once

inline HeapAllocator* HeapAllocator::Create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks)
{
    HeapAllocator* TheHeapAllocator = reinterpret_cast<HeapAllocator*>(i_pHeapMemory);
    i_pHeapMemory = TheHeapAllocator + 1;
    i_HeapMemorySize -= sizeof(HeapAllocator);

    return new (TheHeapAllocator) HeapAllocator(i_pHeapMemory, i_HeapMemorySize, i_NumMemBlocks);
}

inline MemoryBlock* HeapAllocator::GetMemoryBlock()
{
    if (pFreeMemBlocks == nullptr)
        return nullptr;

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

inline void HeapAllocator::ShowOutstandingAllocations()
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

inline void HeapAllocator::ShowFreeBlocks()
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

inline void HeapAllocator::Destroy()
{
    while (pOutstandingAllocations != nullptr)
    {
        MemoryBlock* ptr = pOutstandingAllocations;
        pOutstandingAllocations = pOutstandingAllocations->pNextBlock;
        free(ptr);
    }
    Coalesce();
    assert(!pOutstandingAllocations);
}