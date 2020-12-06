#include "machine_state.h"

MachineState::MachineState(uint32_t initial_pc, std::vector <uint32_t> &words, uint32_t num_pages)
: pc(initial_pc), mmu(words , num_pages) {
    for (size_t i = 0; i < regs_num; i++) {
        if (i == 2)
            regs[i] = 0x4ffc;
        else
            regs[i] = 0;
    }
    //memory.resize(words.size() * sizeof(uint32_t));
    //memcpy(&(memory[0]), (void *) words.data(), words.size() * sizeof(uint32_t));
}


