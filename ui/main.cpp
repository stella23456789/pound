#include "cpu.h"
#include "jit.h"

#include <cstdio>

int main()
{
    CPU cpu;
    cpu.pc = 0;

    // Simple ARMv8 program in memory (MOVZ X0, #5; ADD X0, X0, #3; RET)
    // These are placeholders; real encoding will be parsed later
    cpu.memory[0] = 0x05; // MOVZ placeholder
    cpu.memory[4] = 0x03; // ADD placeholder
    cpu.memory[8] = 0xFF; // RET placeholder

    JIT jit;
    jit.translate_and_run(cpu);

    printf("X0 = %llu\n", cpu.regs[0]);
    return 0;
}