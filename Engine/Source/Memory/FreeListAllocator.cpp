#include "FreeListAllocator.h"

#include "AllocatorUtility.h"
#include "Core/Math.h"
#include "Exception/ArgumentException.h"
#include "Exception/NullPointerException.h"
#include "Exception/OutOfMemoryException.h"

using namespace ArtemisEngine;

FreeListAllocator::FreeListAllocator() : BaseAllocator(), AllBlocks(nullptr)
{
}

FreeListAllocator::FreeListAllocator(void* start, size_t size) : BaseAllocator(start, size), AllBlocks(static_cast<MemoryBlock*>(start))
{
	Assert(size > sizeof(MemoryBlock), ArgumentException("Size must at least be as large as memory block"))
	
	AllBlocks->Size = size;
	AllBlocks->Next = nullptr;
}

void* FreeListAllocator::Allocate(size_t size, uint8 alignment)
{
	Assert(size > 0, ArgumentException("Cannot allocate memory of non-positive size"))
	Assert(alignment > 0, ArgumentException("Cannot allocate memory with an alignment of 0"))
	Assert(Math::IsPowerOfTwo(alignment), ArgumentException("Alignment must be power of two!"))

	// We sort by smallest block available.
	// Might want to expand in the future to support other sorting requirements.
	MemoryBlock* bestBlock = nullptr;
	MemoryBlock* bestBlockPrevious = nullptr;
	MemoryBlock* previousBlock = nullptr;
	MemoryBlock* currentBlock = AllBlocks;
	size_t bestSize = 0;
	uint8 bestAdjustment = 0;
	
	while(currentBlock != nullptr)
	{
		const uint8 adjustment = AllocatorUtility::GetMemoryAddressAdjustmentWithHeader(currentBlock, alignment, sizeof(AllocationHeader));
		const size_t totalSizeToAllocate = size + adjustment;
		
		if(currentBlock->Size >= totalSizeToAllocate && (bestBlock == nullptr || currentBlock->Size < bestBlock->Size))
		{
			bestBlock = currentBlock;
			bestBlockPrevious = previousBlock;
			bestSize = totalSizeToAllocate;
			bestAdjustment = adjustment;
		}

		previousBlock = currentBlock;
		currentBlock = currentBlock->Next;
	}

	Assert(bestBlock != nullptr, OutOfMemoryException("Couldn't find free block large enough for allocation"));

	const uintptr_t bestAddress = AllocatorUtility::GetAddress(bestBlock);
	const size_t remainingSize = bestBlock->Size - bestSize;

	if(remainingSize < sizeof(AllocationHeader))
	{
		bestSize = bestBlock->Size;

		if(bestBlockPrevious != nullptr)
		{
			bestBlockPrevious->Next = bestBlock->Next;
		}
		else
		{
			AllBlocks = bestBlock->Next;
		}
	}
	else
	{
		const uintptr_t newAddress = bestAddress + bestSize;
		MemoryBlock* const newBlock = SetBlock(newAddress, bestBlock->Size - bestSize, bestBlock->Next);

		if(bestBlockPrevious != nullptr)
		{
			bestBlockPrevious->Next = newBlock;
		}
		else
		{
			AllBlocks = newBlock;
		}
	}
		
	const uintptr_t alignedAddress = bestAddress + bestAdjustment;
	auto* const header = AllocatorUtility::GetPointer<AllocationHeader>(alignedAddress - sizeof(AllocationHeader));
	header->Size = bestSize;
	header->Adjustment = bestAdjustment;

	return AllocatorUtility::GetPointer<void>(alignedAddress);
}

void FreeListAllocator::Deallocate(const void* const object)
{
	Assert(object != nullptr, ArgumentException("Can't deallocate nullptr"))
	Assert(!IsOutOfBounds(object), ArgumentException("Can't deallocate object that isn't managed by this allocator"));

	auto* const header = AllocatorUtility::SubtractPointer<AllocationHeader>(object, sizeof(AllocationHeader));

	const uintptr_t blockAddress = AllocatorUtility::GetAddress(object) - header->Adjustment;
	auto* const block = AllocatorUtility::GetPointer<MemoryBlock>(blockAddress);

	MemoryBlock* previousBlock = nullptr;
	MemoryBlock* currentBlock = AllBlocks;

	while(currentBlock != nullptr)
	{
		if(AllocatorUtility::GetAddress(currentBlock) >= blockAddress + header->Size)
			break;

		previousBlock = currentBlock;
		currentBlock = currentBlock->Next;
	}

	if(previousBlock == nullptr)
	{
		previousBlock = SetBlock(block, header->Size, AllBlocks);
		AllBlocks = previousBlock;
	}
	else if(AllocatorUtility::GetAddress(previousBlock) + previousBlock->Size == blockAddress)
	{
		previousBlock->Size += header->Size;
	}
	else
	{
		auto* temp = SetBlock(block, header->Size, previousBlock->Next);

		previousBlock->Next = temp;
		previousBlock = temp;
	}

	Assert(previousBlock != nullptr, NullPointerException("Couldn't deallocate memory"))

	// Merge with the next block if we align perfectly
	if (AllocatorUtility::GetAddress(previousBlock) + previousBlock->Size == AllocatorUtility::GetAddress(previousBlock->Next))
	{
		previousBlock->Size += previousBlock->Next->Size;
		previousBlock->Next = previousBlock->Next->Next;
	}
}

FreeListAllocator::MemoryBlock* FreeListAllocator::SetBlock(MemoryBlock* const block, const size_t size, MemoryBlock* const next)
{
	block->Size = size;
	block->Next = next;
	return block;
}

FreeListAllocator::MemoryBlock* FreeListAllocator::SetBlock(uintptr_t address, size_t size, MemoryBlock* next)
{
	return SetBlock(AllocatorUtility::GetPointer<MemoryBlock>(address), size, next);
}
