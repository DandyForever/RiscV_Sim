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

    void SetSatp(uint32_t value);

    void SetPC(uint32_t value);

    void SetReg(uint8_t num, uint32_t value);

    uint32_t GetSatp();

    uint32_t GetPC();

    uint32_t GetReg(uint8_t num);

    void WriteWord(uint32_t va, uint32_t data);

    void WriteHalfWord(uint32_t va, uint16_t data);

    void WriteByte(uint32_t va, uint8_t data);

    uint32_t ReadWord(uint32_t va);

    uint16_t ReadHalfWord(uint32_t va);

    uint8_t ReadByte(uint32_t va);

    uint32_t Fetch(uint32_t va);

    uint32_t GetCmdCount();

    void IncreaseCmdCount();

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
