#include "MemorySystem.h"
#include "HeapAllocator.h"
#include "FixedSizeAllocator.h"
#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>

HeapAllocator* pHeapAllocator;
FixedSizeAllocator* fsa16;
FixedSizeAllocator* fsa32;
FixedSizeAllocator* fsa96;
bool destroying = false;

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	pHeapAllocator = HeapAllocator::Create(i_pHeapMemory,i_sizeHeapMemory,i_OptionalNumDescriptors);
	fsa96 = FixedSizeAllocator::Create(96, 400, pHeapAllocator);
	fsa32 = FixedSizeAllocator::Create(32, 200, pHeapAllocator);
	fsa16 = FixedSizeAllocator::Create(16, 100, pHeapAllocator);
	return true;
}

void Collect()
{
	pHeapAllocator->Coalesce();
}

void DestroyMemorySystem()
{
	destroying = true;
	pHeapAllocator->Destroy();
	// Destroy your HeapManager and FixedSizeAllocators
}

void* __cdecl malloc(size_t i_size)
{
	void* returnPtr = nullptr;

	if (i_size <= 16)
		returnPtr = fsa16->alloc();
	else if (i_size <= 32)
		returnPtr = fsa32->alloc();
	else if (i_size <= 96)
		returnPtr = fsa96->alloc();
	else
		returnPtr = pHeapAllocator->alloc(i_size);

	printf("malloc %zu\n", i_size);


	return returnPtr;

}

void __cdecl free(void* i_ptr)
{
	if (destroying)
	{
		return;
	}

	if (fsa16->isAllocated(i_ptr))
	{
		fsa16->free(i_ptr);
		return;
	}
	else if (fsa32->isAllocated(i_ptr))
	{
		fsa32->free(i_ptr);
		return;
	}
	else if (fsa96->isAllocated(i_ptr))
	{
		fsa96->free(i_ptr);
		return;
	}
	else
		pHeapAllocator->freeMem(i_ptr);

	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	return;
}

void* operator new(size_t i_size)
{
	void* returnPtr = nullptr;

	if (i_size <= 16)
		returnPtr = fsa16->alloc();
	else if (i_size <= 32)
		returnPtr = fsa32->alloc();
	else if (i_size <= 96)
		returnPtr = fsa96->alloc();
	else
		returnPtr = pHeapAllocator->alloc(i_size);

	printf("malloc %zu\n", i_size);


	return returnPtr;
}

void operator delete(void* i_ptr)
{
	if (fsa16->isAllocated(i_ptr))
	{
		fsa16->free(i_ptr);
		return;
	}
	else if (fsa32->isAllocated(i_ptr))
	{
		fsa32->free(i_ptr);
		return;
	}
	else if (fsa96->isAllocated(i_ptr))
	{
		fsa96->free(i_ptr);
		return;
	}
	else
		pHeapAllocator->freeMem(i_ptr);

	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	return;
}

void* operator new[](size_t i_size)
{
	void* returnPtr = nullptr;

	if (i_size <= 16)
		returnPtr = fsa16->alloc();
	else if (i_size <= 32)
		returnPtr = fsa32->alloc();
	else if (i_size <= 96)
		returnPtr = fsa96->alloc();
	else
		returnPtr = pHeapAllocator->alloc(i_size);

	printf("malloc %zu\n", i_size);


	return returnPtr;
}

void operator delete [](void* i_ptr)
{
	if (fsa16->isAllocated(i_ptr))
	{
		fsa16->free(i_ptr);
		return;
	}
	else if (fsa32->isAllocated(i_ptr))
	{
		fsa32->free(i_ptr);
		return;
	}
	else if (fsa96->isAllocated(i_ptr))
	{
		fsa96->free(i_ptr);
		return;
	}
	else
		pHeapAllocator->freeMem(i_ptr);

	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	return;
}

