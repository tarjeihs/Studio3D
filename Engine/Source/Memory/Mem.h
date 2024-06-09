#pragma once

#include <assert.h>
#include <cstdlib> // For std::malloc and std::free
#include <type_traits>

#include "../../../Math/Source/MathTypes.h"

template<typename TClassTo>
static inline TClassTo* Cast(void* Pointer)
{
    if constexpr (std::is_convertible_v<void*, TClassTo*>)
    {
        return static_cast<TClassTo*>(Pointer);
    }
    else
    {
        return reinterpret_cast<TClassTo*>(Pointer);
    }
}

namespace Mem
{
    
    template<typename TObject>
    static TObject* Malloc(size_t Count = 1)
    {
        void* Block = std::malloc(Count * sizeof(TObject));
        if (Block == nullptr)
        {
            assert("Failed to allocate memory.");
        } 
        return Cast<TObject>(Block);
    }

    template<typename TObject>
    static TObject* Calloc(size_t Count = 1)
    {
        void* Block = std::calloc(Count, sizeof(TObject));
        if (Block == nullptr)
        {
            assert("Failed to allocate memory.");
        } 
        return Cast<TObject>(Block);
    }

    /* Trivial for character arrays or initialize memory to zero state */
    static void Memset(void* Pointer, int32 Value, size_t Size)
    {
        unsigned char* Block = Cast<unsigned char>(Pointer);

        for (size_t Index = 0; Index < Size; ++Index)
        {
            Block[Index] = Value;
        }
    }
}
