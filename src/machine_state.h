#pragma once

#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>
#include "mmu.h"

class MachineState {
public:
    const size_t regs_num = 33;

    MachineState(uint32_t initial_pc, std::vector <uint32_t> &words, uint32_t num_pages);

    ~MachineState() {}
    inline void SetSatp(uint32_t value) { mmu.SetSatp(value); }

    inline void SetPC(uint32_t value) { pc = value; }

    inline void SetReg(uint8_t num, uint32_t value) {
    if (num >= regs_num)
        errx(EXIT_FAILURE, "Such register (%d) doesn't exist", num);
    else
        regs[num] = value;
}

    inline uint32_t GetSatp() { return mmu.GetSatp(); }

    inline uint32_t GetPC() { return pc; }

    inline uint32_t GetReg(uint8_t num) {
    if (num >= regs_num)
        errx(EXIT_FAILURE, "Such register (%d) doesn't exist", num);
    return regs[num];
}

//uint8_t right_shifted_byte(uint32_t data, size_t shift) { return (uint8_t)(data >> shift); }

    inline void WriteWord(uint32_t va, uint32_t data) {
    /*if (va + 3 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    memory[va] = right_shifted_byte(data, 0);
    memory[va + 1] = right_shifted_byte(data, 8);
    memory[va + 2] = right_shifted_byte(data, 16);
    memory[va + 3] = right_shifted_byte(data, 24);*/
    mmu.WriteWordVirtAddr(va, data);
}

    inline void WriteHalfWord(uint32_t va, uint16_t data) {
    /*if (va + 1 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    memory[va] = right_shifted_byte(data, 0);
    memory[va + 1] = right_shifted_byte(data, 8);*/
    mmu.WriteHalfWordVirtAddr(va, data);
}

    inline void WriteByte(uint32_t va, uint8_t data) {
    /*if (va > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    memory[va] = right_shifted_byte(data, 0);*/
        mmu.WriteByteVirtAddr(va, data);
    }

//uint32_t left_shifted_word(uint8_t data, size_t shift) { return (uint32_t) data << shift; }

    inline uint32_t ReadWord(uint32_t va) {
    /*if (va + 3 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    return left_shifted_word(memory[va + 3], 24) |
           left_shifted_word(memory[va + 2], 16) |
           left_shifted_word(memory[va + 1], 8) |
           left_shifted_word(memory[va], 0);*/
        return mmu.ReadWordVirtAddr(va);
    }

    inline uint16_t ReadHalfWord(uint32_t va) {
    /*if (va + 1 > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    return (uint16_t)(left_shifted_word(memory[va + 1], 8) |
                      left_shifted_word(memory[va], 0));*/
        return mmu.ReadHalfWordVirtAddr(va);
    }

    inline uint8_t ReadByte(uint32_t va) {
    /*if (va > memory.size())
        errx(EXIT_FAILURE, "Such address (%#010x) is OOM", va);

    return memory[va];*/
        return mmu.ReadByteVirtAddr(va);
    }

    inline uint32_t Fetch(uint32_t va) {
        return mmu.Fetch(va);
    }

    inline void IncreaseCmdCount(uint32_t value)
    {
        cmd_counter += value;
    }
    inline uint32_t GetCmdCount ()
    {
        return cmd_counter;
    }
    void DumpRegs()
    {
        for (int i = 0; i < 33; i++) {
            if (regs[i] != 0)
                std::cout << "[" << std::dec << i << "] = " << std::dec << regs[i] << std::endl;
        }
    }

private:
    uint32_t pc;
    uint32_t regs[33];
    MMU mmu;
    uint32_t cmd_counter = 0;
    //std::vector<uint8_t> memory;
};
