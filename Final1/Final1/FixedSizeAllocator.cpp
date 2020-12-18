#include "FixedSizeAllocator.h"


FixedSizeAllocator::FixedSizeAllocator(size_t i_blockSize, size_t i_numbOfBlocks, HeapAllocator* i_pAllocator)
{
    fixedSize = i_blockSize;
    numberOfBlocks = i_numbOfBlocks;
    indexList = BitArray::Create(i_blockSize * i_numbOfBlocks, false, i_pAllocator);
    baseAddress = i_pAllocator->alloc(i_blockSize * i_numbOfBlocks);
}

FixedSizeAllocator::~FixedSizeAllocator()
{
    if (!indexList->AreAllBitsSet())
    {
        std::cout << "Allocations present";
        assert(false);
    }
    free(indexList);
    free(baseAddress);
}

void* FixedSizeAllocator::alloc()
{
    size_t firstSetBit;

    if (indexList->GetFirstSetBit(firstSetBit))
    {
        indexList->ClearBit(firstSetBit);
        return reinterpret_cast<void*>(reinterpret_cast<char*>(baseAddress) + (firstSetBit * fixedSize));
    }
    else
    {
        std::cout << "No blocks availible \n";
        return nullptr;
    }
}

void FixedSizeAllocator::free(void* i_ptr)
{
    if (i_ptr == nullptr)
        return;

    if ((reinterpret_cast<char*>(i_ptr) - reinterpret_cast<char*>(baseAddress)) % fixedSize != 0)
    {
        std::cout << "Address is not valid \n";
        return;
    }



    size_t bitIndex = (reinterpret_cast<char*>(i_ptr) - reinterpret_cast<char*>(baseAddress)) / fixedSize;

    if (indexList->isBitSet(bitIndex))
    {
        std::cout << "Bit is already free \n";
        return;
    }
    else
    {
        indexList->SetBit(bitIndex);
        return;
    }
}
