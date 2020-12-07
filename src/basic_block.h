#pragma once
#include "machine_state.h"
#include "decoder.h"
#include "instruction.h"
#include "exec.h"

class BasicBlock
{
private:
    static const uint32_t block_size = 8;
    std::array<Instruction, block_size + 1> instructions;
public:
    BasicBlock() = default;
    BasicBlock (MachineState& state, Decoder& decoder) noexcept;
    inline void Execute (MachineState& state)
    {
        instructions.front().Exec(&(instructions.front()), &state);  
    }
};


