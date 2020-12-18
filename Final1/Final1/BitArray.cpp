#include "BitArray.h"


BitArray::BitArray(size_t i_numBits, bool i_startClear)
{
	numberOfElements = i_numBits / bitsPerElement;
	bitData = (t_BitData*)malloc(numberOfElements * sizeof(t_BitData));
	if (i_startClear)
		ClearAll();
	else
		SetAll();
}

BitArray* BitArray::Create(size_t i_numBits, bool i_startClear, HeapAllocator* i_pAllocator)
{
	void* bitArrayLocation = i_pAllocator->alloc(sizeof(BitArray));
	return new (bitArrayLocation) BitArray(i_numBits,i_startClear);
}

BitArray::~BitArray()
{
	ClearAll();
	free(bitData);
}

bool BitArray::operator[](size_t i_index) const
{
	assert(i_index / bitsPerElement < numberOfElements);

	return bitData[i_index / bitsPerElement] & (t_BitData(1) << i_index % bitsPerElement);
}
