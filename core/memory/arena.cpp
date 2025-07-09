#include "arena.h"
#include "Base/Assert.h"
#ifndef WIN32
#include <sys/mman.h>
#endif

Memory::Arena Memory::arena_init() {
    // TODO(GloriousEggroll): Replace malloc with a windows memory mapping API.
#ifdef WIN32
    auto data =
        static_cast<uint8_t*>(malloc(sizeof(uint8_t) * MEMORY_CAPACITY));
#else
    void* data = mmap(nullptr, MEMORY_CAPACITY, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
    if (data == MAP_FAILED) {
        return {0, 0, nullptr};  // Return invalid arena on failure
    }
    Memory::Arena arena = {
        .capacity = MEMORY_CAPACITY,
        .size = 0,
        .data = static_cast<uint8_t*>(data),
    };
    return arena;
}
// new more memsafe code (ownedbywuigi) (i give up on windows compatibility for now, will stick to the old unsafe code)

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
