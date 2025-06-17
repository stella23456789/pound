#include "jit.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/mman.h>
#endif

#include <cstring>
#include <cstdio>
#include <vector>

using JitFunc = void (*)();

void JIT::translate_and_run(CPU &cpu)
{
#ifdef WIN32
    uint8_t *code = (uint8_t*)VirtualAlloc(NULL, 64, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    uint8_t *code = (uint8_t *)mmap(nullptr, 64, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
#endif

    size_t offset = 0;

    // Decode mock instructions from cpu.memory
    if (cpu.memory[0] == 0x05)
    {                          // MOVZ placeholder
        code[offset++] = 0x48; // mov rax, imm64
        code[offset++] = 0xB8;
        uint64_t imm = 5;
        std::memcpy(&code[offset], &imm, sizeof(imm));
        offset += 8;
    }

    if (cpu.memory[4] == 0x03)
    {                          // ADD placeholder
        code[offset++] = 0x48; // add rax, imm32
        code[offset++] = 0x05;
        uint32_t addval = 3;
        std::memcpy(&code[offset], &addval, sizeof(addval));
        offset += 4;
    }

    code[offset++] = 0xC3; // ret

    JitFunc fn = reinterpret_cast<JitFunc>(code);
    uint64_t result;
    asm volatile(
        "call *%1\n"
        "mov %%rax, %0\n"
        : "=r"(result)
        : "r"(fn)
        : "%rax");

    cpu.regs[0] = result;
}
