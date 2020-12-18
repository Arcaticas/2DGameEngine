#pragma once


inline void BitArray::ClearAll()
{
	for (size_t i = 0; i < numberOfElements; i++)
	{
		bitData[i] = 0;
	}
}

inline void BitArray::SetAll()
{
	for (size_t i = 0; i < numberOfElements; i++)
	{
#ifdef WIN32
		bitData[i] = UINT32_MAX;
#else
		bitData[i] = UINT64_MAX;
#endif
	}
}

inline bool BitArray::AreAllBitsClear() const
{
	for (size_t i = 0; i < numberOfElements; i++)
	{
		if (bitData[i] != 0)
			return false;
	}
	return true;
}

inline bool BitArray::AreAllBitsSet() const
{
	for (size_t i = 0; i < numberOfElements; i++)
	{
#ifdef WIN32
		if (bitData[i] != UINT32_MAX)
			return false;
#else
		if (bitData[i] != UINT64_MAX)
			return false;
#endif
	}
	return true;
}

inline bool BitArray::isBitSet(size_t i_bitNumber) const //implement [] first
{

	return bitData[i_bitNumber / bitsPerElement] & (t_BitData(1) << i_bitNumber % bitsPerElement);
}

inline bool BitArray::isBitClear(size_t i_bitNumber) const //implement [] first
{
	return !(bitData[i_bitNumber / bitsPerElement] & (t_BitData(1) << i_bitNumber % bitsPerElement));
}

inline void BitArray::SetBit(size_t i_bitNumber)
{
	assert(i_bitNumber / bitsPerElement < numberOfElements);

	if (bitData[i_bitNumber / bitsPerElement] & (t_BitData(1) << i_bitNumber % bitsPerElement))
		return;
	else
	{
		t_BitData mask = t_BitData(1) << (i_bitNumber % bitsPerElement);
		bitData[i_bitNumber / bitsPerElement] |= mask;
	}

}

inline void BitArray::ClearBit(size_t i_bitNumber)
{
	assert(i_bitNumber / bitsPerElement < numberOfElements);

	if (!(bitData[i_bitNumber / bitsPerElement] & (t_BitData(1) << i_bitNumber % bitsPerElement)))
		return;
	else
	{
		t_BitData mask = t_BitData(1) << (i_bitNumber % bitsPerElement);
		bitData[i_bitNumber / bitsPerElement] &= ~(mask);
	}
}

inline bool BitArray::GetFirstSetBit(size_t& o_bitNumber)
{
	unsigned long index;
	for (size_t i = 0; i < numberOfElements; i++)
	{
		if (bitData[i] != 0)
		{
#ifdef WIN32
			_BitScanForward(&index, bitData[i]);
#else
			_BitScanForward64(&index, bitData[i]);
#endif
			o_bitNumber = (i * bitsPerElement) + index;
			return true;
		}
	}
	std::cout << "No set bit found. \n";
	return false;
}

inline bool BitArray::GetFirstClearBit(size_t& o_bitNumber)
{
	unsigned long index;
	for (size_t i = 0; i < numberOfElements; i++)
	{
		if (~bitData[i] != 0)
		{
#ifdef WIN32
			_BitScanForward(&index, bitData[i]);
#else
			_BitScanForward64(&index, ~bitData[i]);
#endif
			std::cout << index;
			o_bitNumber = (i * bitsPerElement) + index;
			return true;
		}
	}
	std::cout << "No clear bit found. \n";
	return false;
}