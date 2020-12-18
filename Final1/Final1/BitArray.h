#pragma once
#include "HeapAllocator.h"
#include <cstdint>
#include <vcruntime_string.h>
#include <iostream>
#include <cassert>


class HeapAllocator;

class BitArray
{
#ifdef WIN32
	typedef uint32_t t_BitData;
#else
	typedef uint64_t t_BitData;
#endif //32 or 64 bit configuration


private:

	const size_t bitsPerElement = sizeof(t_BitData) * 8;
	size_t numberOfElements;


public:
	t_BitData* bitData;

	BitArray(size_t i_numBits, bool i_setToZero);

	static BitArray* Create(size_t i_numBits, bool i_startClear, HeapAllocator * i_pAllocator);
	~BitArray();

	size_t GetBitsPerElement() { return bitsPerElement; }
	size_t GetNumberOfElements() { return numberOfElements; }

	inline void ClearAll();
	inline void SetAll();

	inline bool AreAllBitsClear() const;
	inline bool AreAllBitsSet() const;

	inline bool isBitSet(size_t bitNumber) const;
	inline bool isBitClear(size_t bitNumber) const;

	inline void SetBit(size_t bitNumber);
	inline void ClearBit(size_t bitNumber);

	inline bool GetFirstSetBit(size_t& o_bitNumber);
	inline bool GetFirstClearBit(size_t& o_bitNumber);

	bool operator[](size_t i_index) const;
};

#include "BitArray-inl.h"
