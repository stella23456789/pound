#ifndef JIT_H
#define JIT_H
#include "ARM/cpu.h"

class JIT
{
public:
    void translate_and_run(CPU &cpu);
};

#endif