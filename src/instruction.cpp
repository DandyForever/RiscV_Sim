#include "instruction.h"

uint16_t Instruction::GetHash() const {
    return (opcode >> 2) | (funct3 << 5) | (funct7 << 8);
}

uint8_t Instruction::GetRd() const {
    return rd;
}

uint8_t Instruction::GetFunct3() const {
    return funct3;
}

uint8_t Instruction::GetRs1() const {
    return rs1;
}

uint8_t Instruction::GetRs2() const {
    return rs2;
}

uint8_t Instruction::GetFunct7() const {
    return funct7;
}

uint32_t Instruction::GetImm() const {
    return imm;
}

void Instruction::SetRd(uint8_t rd) {
    this.rd = rd;
}

void Instruction::SetFunct3(uint8_t f3) {
    this.funct3 = funct3;
}

void Instruction::SetRs1(uint8_t RS1) {
    this.rs1 = rs1;
}

void Instruction::SetRs2(uint8_t RS2) {
    this.rs2 = rs2;
}

void Instruction::SetFunct7(uint8_t funct7) {
    this.funct7 = funct7;
}

void Instruction::SetImm(uint32_t IMM) {
    this.imm = imm;
}

void Instruction::SetCommand (const char* name, void (*cmd) (const Instruction*, State*))
{
    this.name = name;
    this.cmd = command;
}

void Instruction::Exec(State *state) {
    cmd(this, state);
}