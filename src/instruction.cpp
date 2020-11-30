#include "instruction.h"

uint16_t Instruction::GetHash(uint8_t opcode) const {
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
    this->rd = rd;
}

void Instruction::SetFunct3(uint8_t funct3) {
    this->funct3 = funct3;
}

void Instruction::SetRs1(uint8_t rs1) {
    this->rs1 = rs1;
}

void Instruction::SetRs2(uint8_t rs2) {
    this->rs2 = rs2;
}

void Instruction::SetFunct7(uint8_t funct7) {
    this->funct7 = funct7;
}

void Instruction::SetImm(uint32_t imm) {
    this->imm = imm;
}

void Instruction::SetCommand (const char* name, void (*cmd) (const Instruction*, MachineState*))
{
    this->name = name;
    this->cmd = cmd;
}

void Instruction::Exec(MachineState *state) {
    cmd(this, state);
}

void Instruction::PrintInstr (const bool is_verbose)
{
    if (is_verbose)
    {
        printf ("rd     : %u\n", rd);
        printf ("funct3 : %u\n", funct3);
        printf ("rs1    : %u\n", rs1);
        printf ("rs2    : %u\n", rs2);
        printf ("funct7 : %u\n", funct7);
        printf ("imm    : %u\n\n", imm);
    }
}
