#pragma once

#include <vector>
#include <mutex>
#include <cassert>

#include "Core/Engine.h"
#include "Core/UUID.h"
#include "Memory/Mem.h"
#include "Memory/Memory.h"

class CObject
{
	static std::mutex ObjectAllocatorMutex;

public:
	void* operator new(SizeType Size)
	{
		std::lock_guard<std::mutex> Lock(ObjectAllocatorMutex);
		void* Pointer = std::malloc(Size);
		assert(Pointer && "Bad allocation.");
		GetEngine()->Metrics.CurrentObjectAllocated++;
		GetEngine()->Metrics.TotalObjectAllocated++;
		GetEngine()->Metrics.CurrentSizeAllocated+=Size;
		GetEngine()->Metrics.TotalSizeAllocated+=Size;

		return Pointer;
	}

	void operator delete(void* Pointer, size_t Size) {
        std::lock_guard<std::mutex> Lock(ObjectAllocatorMutex);
        std::free(Pointer);
        GetEngine()->Metrics.CurrentObjectAllocated--;
        GetEngine()->Metrics.CurrentSizeAllocated -= Size;
    }

	const SUUID& GetUUID() const
	{
		return UUID;
	}
	
private:
	SUUID UUID;
};