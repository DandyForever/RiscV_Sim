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

void machineState::SetSatp(uint32_t value) { mmu.SetSatp(value); }

void MachineState::SetPC(uint32_t value) { pc = value; }

void MachineState::SetReg(uint8_t num, uint32_t value) {
    if (num >= regs_num)
        errx(EXIT_FAILURE, "Such register (%d) doesn't exist", num);
    else
        regs[num] = value;
}

uint32_t MachineState::GetSatp() { return mmu.GetSatp(); }

uint32_t MachineState::GetPC() { return pc; }

uint32_t MachineState::GetReg(uint8_t num) {
    if (num >= regs_num)
        errx(EXIT_FAILURE, "Such register (%d) doesn't exist", num);
    return regs[num];
}

//uint8_t right_shifted_byte(uint32_t data, size_t shift) { return (uint8_t)(data >> shift); }

void MachineState::WriteWord(uint32_t va, uint32_t data) {
    /*if (va + 3 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    memory[va] = right_shifted_byte(data, 0);
    memory[va + 1] = right_shifted_byte(data, 8);
    memory[va + 2] = right_shifted_byte(data, 16);
    memory[va + 3] = right_shifted_byte(data, 24);*/
    mmu.writeWordVirtAddr(va, data);
}

void MachineState::WriteHalfWord(uint32_t va, uint16_t data) {
    /*if (va + 1 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    memory[va] = right_shifted_byte(data, 0);
    memory[va + 1] = right_shifted_byte(data, 8);*/
    mmu.WriteHalfWordVirtAddr(va, data);
}

void MachineState::WriteByte(uint32_t va, uint8_t data) {
    /*if (va > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    memory[va] = right_shifted_byte(data, 0);*/
    mmu.WriteByteVirtAddr(va, data);
}

//uint32_t left_shifted_word(uint8_t data, size_t shift) { return (uint32_t) data << shift; }

uint32_t MachineState::ReadWord(uint32_t va) {
    /*if (va + 3 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    return left_shifted_word(memory[va + 3], 24) |
           left_shifted_word(memory[va + 2], 16) |
           left_shifted_word(memory[va + 1], 8) |
           left_shifted_word(memory[va], 0);*/
    return mmu.ReadWordVirtAddr(va);
}

uint16_t MachineState::ReadHalfWord(uint32_t va) {
    /*if (va + 1 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    return (uint16_t)(left_shifted_word(memory[va + 1], 8) |
                      left_shifted_word(memory[va], 0));*/
    return mmu.ReadHalfWordVirtAddr(va);
}

uint8_t MachineState::ReadByte(uint32_t va) {
    /*if (va > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    return memory[va];*/
    return mmu.ReadByteVirtAddr(va);
}

uint32_t MachineState::Fetch(uint32_t va) {
    return mmu.Fetch(va);
}

inline void MachineState::IncreaseCmdCount()
{
    cmd_counter++;
}
inline uint32_t MachineState::GetCmdCount ()
{
    return cmd_counter;
}