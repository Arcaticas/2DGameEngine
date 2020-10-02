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
private:
    HeapAllocator(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks);

    MemoryBlock* InitializeMemoryBlocks(void* i_pBlocksMemory, size_t i_BlocksMemorySize);
    MemoryBlock* GetMemoryBlock();
    void ReturnMemoryBlock(MemoryBlock* i_pFreeBlock);
    void* alloc(size_t size);

    struct MemoryBlock* pFreeMemBlocks;
    struct MemoryBlock* pFreeList;
    struct MemoryBlock* pOutstandingAllocations;
};



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
    assert(pFreeList != nullptr);

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

void* HeapAllocator::alloc(size_t size)
{
    MemoryBlock* baseBlock = GetMemoryBlock();

    MemoryBlock* free = pFreeList;
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
    //move back from the end of the memory block
    baseBlock->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<char*>(back)-size-(size%4));
    baseBlock->BlockSize = size + (size % 4);

    if (pOutstandingAllocations == nullptr)
    {
        pOutstandingAllocations = baseBlock;
    }
    else
    {
        baseBlock->pNextBlock = pOutstandingAllocations;
        pOutstandingAllocations = baseBlock;
    }

    free->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<char*>(free->pBaseAddress) + size);
    free->BlockSize -= size + (size % 4);

}
