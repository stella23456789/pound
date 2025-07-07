#ifndef POUND_ARENA_H
#define POUND_ARENA_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace Memory {

/* Defines the default size (in bytes) for memory arenas created via arena_init() */
#define MEMORY_CAPACITY 20480  // 20 KB

/*
 *  NAME
 *      Arena - Memory management structure for efficient allocation and de-allocation.
 *
 *  SYNOPSIS
 *      typedef struct {
 *          std::size_t capacity;   Total number of bytes allocated.
 *          std::size_t size;       The current number of bytes consumed.
 *          uint8_t* data;          A pointer to the base address of the allocated memory buffer.
 *      } Arena;
 *
 *  DESCRIPTION
 *      The arena struct handles allocating and managing contiguous memory blocks.
 *
 *  RATIONALE
 *      A memory arena offers a safer alternative to malloc/realloc by
 *      maintaining a single contiguous block eliminates heap fragmentation
 *      that occurs with frequent small allocations.
 */
typedef struct {
    std::size_t capacity;
    std::size_t size;
    uint8_t* data;
} Arena;

/*
 *  NAME
 *      arena_init - Initialize a memory arena with default capacity.
 *
 *  SYNOPSIS
 *      Arena Memory::arena_init();
 *
 *  DESCRIPTION
 *     The function creates and returns a new memory arena instance with a
 *     pre-allocated capacity. See the definition MEMORY_CAPACITY to change the
 *     default capacity.
 *
 *  RETURN VALUE
 *     Returns a valid Arena object on success.
 */
extern Arena arena_init();

/*
 *  NAME
 *      arena_allocate - Allocate memory from a pre-initialized arena.
 *
 *  SYNOPSIS
 *      const uint8_t Memory::arena_allocate(Memory::Arena* arena, std::size_t size);
 *
 *  DESCRIPTION
 *      The function allocates size bytes from the specified arena. It assumes
 *      the arena has sufficient capacity and returns a pointer to the allocated
 *      memory region.
 *
 *  RETURN VALUE
 *      Returns a pointer to the first byte of the allocated memory. The returned
 *      pointer is valid until the arena is reset or destroyed.
 *
 *  NOTES
 *      Requires Arena to be initialized with arena_init() or similar.
 */
const uint8_t* arena_allocate(Arena* arena, std::size_t size);

/*
 *  NAME
 *      arena_reset - Reset a memory arena's allocation size to zero.
 *
 *  SYNOPSIS
 *      void Memory::arena_reset(Memory::Arena* arena);
 *
 *  DESCRIPTION
 *      The function resets the allocation size of a pre-initialized Arena to zero.
 *      This effectively "frees" all memory allocated from the arena without
 *      deallocating the underlying buffer, allowing reuse of the capacity for
 *      future allocations.
 *
 *  NOTES
 *      Resets arena->size to 0 while preserving arena->capacity.
 *      Does not free the underlying memory buffer.
 *      Useful for reusing arenas without reallocation.
 */
void arena_reset(Arena* arena);

/**
 *  NAME
 *      arena_free - Free the memory allocated by an arena
 *
 *  SYNOPSIS
 *      void Memory::arena_free(Memory::Arena* arena);
 *
 *  DESCRIPTION
 *      The function releases the memory buffer associated with a Arena and
 *      resets its capacity and size to zero. This marks the arena as invalid for
 *      future allocation unless reinitialized.
 */
void arena_free(Memory::Arena* arena);

}  // namespace Memory
#endif  //POUND_ARENA_H
