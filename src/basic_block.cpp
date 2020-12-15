#include "basic_block.h"

BasicBlock::BasicBlock (MachineState& state, Decoder& decoder) noexcept
{
    uint32_t i = 0;
    do 
    {
        auto va = state.GetPC() + 4 * i;
        auto cur_instr = state.Fetch(va);
        if (!cur_instr.first) {
            pf_handler(&state, va);
            continue;
        }
        instructions[i] = decoder.Decode(cur_instr.second);
        i++;
    }
    while ((i < block_size) && instructions[i - 1].GetBBEnd());
    instructions[i].SetCommand("BBEND", &BBENDExec);
}

