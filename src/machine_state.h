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

    inline void SetStval(uint32_t value) { stval = value; }

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


    inline bool WriteWord(uint32_t va, uint32_t data) {
        try {
            mmu.WriteWordVirtAddr(va, data);
            return true;
        } catch (PageFaultException& e) {
            std::cout << e.what() << " pte: " << e.GetPte() << std::endl;
            return false;
        }
    }

    inline bool WriteHalfWord(uint32_t va, uint16_t data) {
        try {
            mmu.WriteHalfWordVirtAddr(va, data);
            return true;
        } catch (PageFaultException& e) {
            std::cout << e.what() << " pte: " << e.GetPte() << std::endl;
            return false;
        }
    }

    inline bool WriteByte(uint32_t va, uint8_t data) {
        try {
            mmu.WriteByteVirtAddr(va, data);
            return true;
        } catch (PageFaultException& e) {
            std::cout << e.what() << " pte: " << e.GetPte() << std::endl;
            return false;
        }
    }

    inline std::pair<bool, uint32_t> ReadWord(uint32_t va) {
        try {
            return {true, mmu.ReadWordVirtAddr(va)};
        } catch (PageFaultException& e) {
            std::cout << e.what() << " pte: " << e.GetPte() << std::endl;
            return {false, 0};
        }
    }

    inline std::pair<bool, uint16_t> ReadHalfWord(uint32_t va) {
        try {
            return {true, mmu.ReadHalfWordVirtAddr(va)};
        } catch (PageFaultException& e) {
            std::cout << e.what() << " pte: " << e.GetPte() << std::endl;
            return {false, 0};
        }
    }

    inline std::pair<bool, uint8_t> ReadByte(uint32_t va) {
        try {
            return {true, mmu.ReadByteVirtAddr(va)};
        } catch (PageFaultException& e) {
            std::cout << e.what() << " pte: " << e.GetPte() << std::endl;
            return {false, 0};
        }
    }

    inline std::pair<bool, uint32_t> Fetch(uint32_t va) {
        try {
            return {true, mmu.Fetch(va)};
        } catch (PageFaultException& e) {
            std::cout << e.what() << " pte: " << e.GetPte() << std::endl;
            return {false, 0};
        }
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
    uint32_t stval = 0;
    uint32_t cmd_counter = 0;
};
