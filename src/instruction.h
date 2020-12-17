#pragma once
#include <stdint.h>
#include "machine_state.h"
#include <stdio.h>

class Instruction {
private:
    uint8_t rd = 0;
    uint8_t funct3 = 0;
    uint8_t rs1 = 0;
    uint8_t rs2 = 0;
    uint8_t funct7 = 0;
    uint32_t imm = 0;
    bool BBEnd;
    uint32_t va;

    void (*cmd)(const Instruction *, const Instruction *, MachineState *);

    const char *name;
public:
    Instruction(){}
    inline uint16_t GetHash(uint8_t opcode) const {
        return (opcode >> 2) | (funct3 << 5) | (funct7 << 8);
    }

    inline uint8_t GetRd() const {
        return rd;
    }

    inline uint8_t GetFunct3() const {
        return funct3;
    }

    inline uint8_t GetRs1() const {
        return rs1;
    }

    inline uint8_t GetRs2() const {
        return rs2;
    }

    inline uint8_t GetFunct7() const {
        return funct7;
    }

    inline uint32_t GetImm() const {
        return imm;
    }

    inline uint32_t GetVa() const {
        return va;
    }

    inline void SetVa(uint32_t value) {
        va = value;
    }

    inline void SetRd(uint8_t rd) {
        this->rd = rd;
    }

    inline void SetFunct3(uint8_t funct3) {
        this->funct3 = funct3;
    }

    inline void SetRs1(uint8_t rs1) {
        this->rs1 = rs1;
    }

    inline void SetRs2(uint8_t rs2) {
        this->rs2 = rs2;
    }

    inline void SetFunct7(uint8_t funct7) {
        this->funct7 = funct7;
    }

    inline void SetImm(uint32_t imm) {
        this->imm = imm;
    }

    inline void SetCommand(const char *name, void (*cmd)(const Instruction *, const Instruction *, MachineState *)) {
        this->name = name;
        this->cmd = cmd;
    }

    inline void Exec(const Instruction* first, MachineState *state) const{
        cmd(this, first, state);
    }

    void PrintInstr(const bool is_verbose);

    inline void SetBBEnd(bool flag)
    {
        BBEnd = flag;
    }

    inline bool GetBBEnd () const
    {
        return BBEnd;
    }
};
