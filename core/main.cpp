// Copyright 2025 Pound Emulator Project. All rights reserved.

#include "Base/Logging/Backend.h"

#include "ARM/cpu.h"
#include "JIT/jit.h"

int main() {

    Base::Log::Initialize();
    Base::Log::Start();

    const auto config_dir = Base::FS::GetUserPath(Base::FS::PathType::BinaryDir);
    Config::Load(config_dir / "config.toml");

    CPU cpu;
    cpu.pc = 0;

    // Simple ARMv8 program in memory (MOVZ X0, #5; ADD X0, X0, #3; RET)
    // These are placeholders; real encoding will be parsed later
    cpu.write_byte(0, 0x05); // MOVZ placeholder
    cpu.write_byte(4, 0x03); // ADD placeholder
    cpu.write_byte(8, 0xFF); // RET placeholder

    LOG_INFO(ARM, "{}", cpu.read_byte(0));

    JIT jit;
    jit.translate_and_run(cpu);

    cpu.print_debug_information();

    LOG_INFO(ARM, "X0 = {}", cpu.x(0));

    return 0;
}
