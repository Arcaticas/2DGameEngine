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

bool HeapAllocator::Coalesce()
{
    MemoryBlock* current = pFreeList;
    MemoryBlock* compare;

    MemoryBlock* slowCurr = current;
    MemoryBlock* fastCurr = current;
    bool slowCurrGo = false;

    while (current->pNextBlock != nullptr)
    {
        compare = pFreeList;
        MemoryBlock* slowComp = pFreeList;
        MemoryBlock* fastComp = pFreeList;
        bool slowCompGo = false;

        while (compare->pNextBlock != nullptr)
        {
            if (reinterpret_cast<char*>(current->pBaseAddress) + current->BlockSize == compare->pNextBlock->pBaseAddress)
            {
                current->BlockSize += compare->pNextBlock->BlockSize;
                MemoryBlock* temp = compare->pNextBlock->pNextBlock;

                if (compare->pNextBlock == slowCurr)
                    slowCurr = slowCurr->pNextBlock;

                ReturnMemoryBlock(compare->pNextBlock);
                compare->pNextBlock = temp;
                Coalesce();
            }
            compare = compare->pNextBlock;

            if (slowCompGo)
            {
                slowComp = slowComp->pNextBlock;
            }
            slowCompGo = !slowCompGo;
            fastComp = fastComp->pNextBlock;

            if (slowComp == fastComp)
            {
                break;
            }
        }

        current = current->pNextBlock;

        if (slowCurrGo)
        {
            slowCurr = slowCurr->pNextBlock;
        }

        slowCurrGo = !slowCurrGo;

        fastCurr = fastCurr->pNextBlock;

        if (slowCurr == fastCurr)
        {
            break;
        }
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
    assert(free);

    //find the back of the memory block
    void* back = reinterpret_cast<void*>(reinterpret_cast<char*>(free->pBaseAddress) + size);


    //move back from the end of the memory block
    baseBlock->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<char*>(back) - (size + allignmentCheck));
    baseBlock->BlockSize = size + allignmentCheck;
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
    free->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<char*>(free->pBaseAddress) + size + allignmentCheck);
    free->BlockSize -= size + allignmentCheck;
    //return the address
    return baseBlock->pBaseAddress;
}

bool HeapAllocator::freeMem(void* ptr)
{
    if (ptr == nullptr)
        return false;

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
    return true;
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
    MemoryBlock* out = pOutstandingAllocations;
    MemoryBlock* slow = out;
    MemoryBlock* fast = out;
    bool slowGo = false;

    while (out->pNextBlock)
    {
        std::cout << out->pBaseAddress;
        std::cout << '\n';
        std::cout << out->BlockSize;
        std::cout << '\n';

        out = out->pNextBlock;

        fast = fast->pNextBlock;
        if (slowGo)
            slow = slow->pNextBlock;
        slowGo = !slowGo;

        if (slow == fast)
            break;
    }
}

void HeapAllocator::ShowFreeBlocks()
{
    MemoryBlock* free = pFreeList;
    MemoryBlock* slow = free;
    MemoryBlock* fast = free;
    bool slowGo = false;

    while (free->pNextBlock)
    {
        std::cout << free->pBaseAddress;
        std::cout << '\n';
        std::cout << free->BlockSize;
        std::cout << '\n';

        free = free->pNextBlock;

        fast = fast->pNextBlock;
        if (slowGo)
            slow = slow->pNextBlock;
        slowGo = !slowGo;

        if (slow == fast)
            break;
    }
}

void HeapAllocator::Destroy()
{
    while (pOutstandingAllocations)
    {
        MemoryBlock* temp = pOutstandingAllocations;
        pOutstandingAllocations = pOutstandingAllocations->pNextBlock;
        freeMem(temp);
    }

    while (pFreeList)
    {
        MemoryBlock* temp = pFreeList;
        pFreeList = pFreeList->pNextBlock;
        ReturnMemoryBlock(temp);
    }

    delete this;
}
