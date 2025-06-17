#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include <cstdio>
#include <cstring>

struct CPU {
    uint64_t regs[31] = {0}; // X0–X30
    uint64_t pc = 0;
    static const size_t MEM_SIZE = 64 * 1024;
    uint8_t memory[MEM_SIZE];

    CPU() { std::memset(memory, 0, MEM_SIZE); }

    uint64_t &x(int i) { return regs[i]; }

    uint8_t read_byte(uint64_t addr) {
        if (addr >= MEM_SIZE) {
            printf("%llu out of bounds\n", addr);
        }
        return memory[addr];
    }

    void write_byte(uint64_t addr, uint8_t byte) {
        if (addr >= MEM_SIZE) {
            printf("%llu out of bounds\n", addr);
        }
        memory[addr] = byte;
    }

    void print_debug_information() {
        printf("PC = %llu\n", pc);
        for (int reg = 0; reg < 32; reg++) {
            printf("X%i = %llu\n", reg, x(reg)); // X0 = 0...
        }
    }
};

#endif