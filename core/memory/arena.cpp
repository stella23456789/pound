#include "arena.h"
#include "Base/Assert.h"

Memory::Arena Memory::arena_init() {
    // TODO(GloriousTaco): The line below is stupidly unsafe. Replace malloc with mmap() and check the return value.
    auto data =
        static_cast<uint8_t*>(malloc(sizeof(uint8_t) * MEMORY_CAPACITY));
    Memory::Arena arena = {
        .capacity = MEMORY_CAPACITY,
        .size = 0,
        .data = data,
    };
    return arena;
}
const uint8_t* Memory::arena_allocate(Memory::Arena* arena,
                                      const std::size_t size) {
    ASSERT(arena != nullptr);
    ASSERT(arena->size + size < arena->capacity);
    const uint8_t* const data = &(arena->data[arena->size]);
    arena->size += size;
    return data;
}
void Memory::arena_reset(Memory::Arena* arena) {
    ASSERT(arena != nullptr);
    arena->size = 0;
}
void Memory::arena_free(Memory::Arena* arena) {
    ASSERT(arena != nullptr);
    arena->capacity = 0;
    arena->size = 0;
    // TODO(GloriousTaco): Replace free with a memory safe alternative.
    free(arena->data);
}
