#pragma once


inline FixedSizeAllocator* FixedSizeAllocator::Create(size_t i_blockSize, size_t i_numbOfBlocks, HeapAllocator* i_heapAllocator)
{
    void* fixedSizeAddress = i_heapAllocator->alloc(sizeof(FixedSizeAllocator));
    return new (fixedSizeAddress) FixedSizeAllocator(i_blockSize, i_numbOfBlocks, i_heapAllocator);
}

inline bool FixedSizeAllocator::isAllocated(void* i_ptr)
{
    assert(i_ptr);
    if (i_ptr < baseAddress || i_ptr > reinterpret_cast<void*>(reinterpret_cast<char*>(baseAddress) + (fixedSize * numberOfBlocks)))
    {
        std::cout << "Not allocated in allocator \n";
        return false;
    }
    size_t bitIndex = (reinterpret_cast<char*>(i_ptr) - reinterpret_cast<char*>(baseAddress)) / fixedSize;
    return indexList->isBitClear(bitIndex);
}

inline void FixedSizeAllocator::ShowOutstandingAllocations()
{
    std::cout << "Outstanding allocations in fixed allocator " + fixedSize;
    std::cout << '\n';
    for (int i = 0; i < indexList->GetNumberOfElements(); i++)
    {
        if (indexList->isBitClear(i))
        {
            std::cout << reinterpret_cast<void*>(reinterpret_cast<char*>(baseAddress) + (i * fixedSize));
            std::cout << '\n';
        }
    }
}

inline void FixedSizeAllocator::ShowFreeBlocks()
{
    std::cout << "Free allocations in fixed allocator " + fixedSize;
    std::cout << '\n';
    for (int i = 0; i < indexList->GetNumberOfElements(); i++)
    {
        if (indexList->isBitSet(i))
        {
            std::cout << reinterpret_cast<void*>(reinterpret_cast<char*>(baseAddress) + (i * fixedSize));
            std::cout << '\n';
        }
    }
}