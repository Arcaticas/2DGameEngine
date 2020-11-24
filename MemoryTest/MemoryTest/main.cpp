
#include <cassert>
#include <iostream>
#include "HeapManager_UnitTest.cpp"


int main()
{
	/*
	const size_t            sizeHeap = 1024 * 1024;
	const unsigned int      numDescriptors = 2048;

	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	assert(SysInfo.dwPageSize > 0);

	size_t sizeHeapInPageMultiples = SysInfo.dwPageSize * ((sizeHeap + SysInfo.dwPageSize) / SysInfo.dwPageSize);
	void* pHeapMemory = VirtualAlloc(NULL, sizeHeapInPageMultiples, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	assert(pHeapMemory);

	HeapAllocator* heapManager = HeapAllocator::Create(pHeapMemory,sizeHeap,numDescriptors);
	*/
	bool test = true;
	HeapManager_UnitTest();
	std::cout << test;



	return 0;
}