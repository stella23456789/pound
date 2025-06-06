#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include <cstring>

struct CPU {
    uint64_t regs[31] = {0}; // X0–X30
    uint64_t pc = 0;
    static const size_t MEM_SIZE = 64 * 1024;
    uint8_t memory[MEM_SIZE];

    CPU() { std::memset(memory, 0, MEM_SIZE); }

    uint64_t& x(int i) { return regs[i]; }
};

#endif