#include "basic_block.h"

BasicBlock::BasicBlock (MachineState& state, Decoder& decoder) noexcept
{
    uint32_t i = 0;
    uint32_t cur_instr = 0;
    do 
    {
        cur_instr = state.Fetch(state.GetPC() + 4 * i);
        instructions[i] = decoder.Decode(cur_instr);
        i++;
    }
    while ((i < block_size) && instructions[i - 1].GetBBEnd());
    instructions[i].SetCommand("BBEND", &BBENDExec);
}

