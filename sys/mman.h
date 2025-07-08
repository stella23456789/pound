// mman.h
// only there for Windows compatibility
#ifndef MMAN_H
#define MMAN_H

#if defined(__linux__) || defined(__APPLE__)
// Linux or macOS: Use standard sys/mman.h
#include <sys/mman.h>

#else
// Windows: Define mmap, munmap, and MAP_FAILED
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define MAP_FAILED ((void*)-1)

// Protection and flag constants (minimal subset for your use case)
#define PROT_READ  0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20

// mmap equivalent using VirtualAlloc
inline void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
    (void)addr;   // Ignored (VirtualAlloc doesn't support specific address)
    (void)flags;  // Ignored (simplified for anonymous mapping)
    (void)fd;     // Ignored (no file mapping)
    (void)offset; // Ignored (no file mapping)

    DWORD protect = 0;
    if (prot & PROT_READ && prot & PROT_WRITE) {
        protect = PAGE_READWRITE;
    } else if (prot & PROT_READ) {
        protect = PAGE_READONLY;
    } else {
        return MAP_FAILED; // Unsupported protection
    }

    void* ptr = VirtualAlloc(nullptr, length, MEM_COMMIT | MEM_RESERVE, protect);
    return ptr ? ptr : MAP_FAILED;
}

// munmap equivalent using VirtualFree
inline int munmap(void* addr, size_t length) {
    (void)length; // Ignored (VirtualFree doesn't need length for committed memory)
    BOOL result = VirtualFree(addr, 0, MEM_RELEASE);
    return result ? 0 : -1; // Return 0 on success, -1 on failure
}

#endif

#endif // MMAN_H