#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include "exec.h"
#include "machine_state.h"
#include "instruction.h"

enum class Opcode : uint8_t {
    LUI = 0x37,
    AUIPC = 0x17,
    JAL = 0x6F,
    JALR = 0x67,
    BRANCH = 0x63,
    LOAD = 0x3,
    STORE = 0x23,
    OP_IMM = 0x13,
    OP = 0x33,
    MISC_MEM = 0xF,
    SYSTEM = 0x73,
};

struct Command {
    const char *name;

    void (*cmd)(const Instruction *, const Instruction *, MachineState *);

    Opcode opcode;
    uint8_t funct3 = 0;
    uint8_t funct7 = 0;
};

const Command commandList[] = {
        {"LUI",   &LUIExec,   Opcode::LUI},
        {"AUIPC", &AUIPCExec, Opcode::AUIPC},
        {"JAL",   &JALExec,   Opcode::JAL},
        {"JALR",  &JALRExec,  Opcode::JALR},
        {"BEQ",   &BEQExec,   Opcode::BRANCH},
        {"BNE",   &BNEExec,   Opcode::BRANCH,  0x1},
        {"BLT",   &BLTExec,   Opcode::BRANCH,  0x4},
        {"BGE",   &BGEExec,   Opcode::BRANCH,  0x5},
        {"BLTU",  &BLTUExec,  Opcode::BRANCH,  0x6},
        {"BGEU",  &BGEUExec,  Opcode::BRANCH,  0x7},
        {"LB",    &LBExec,    Opcode::LOAD},
        {"LH",    &LHExec,    Opcode::LOAD,    0x1},
        {"LW",    &LWExec,    Opcode::LOAD,    0x2},
        {"LBU",   &LBUExec,   Opcode::LOAD,    0x4},
        {"LHU",   &LHUExec,   Opcode::LOAD,    0x5},
        {"SB",    &SBExec,    Opcode::STORE},
        {"SH",    &SHExec,    Opcode::STORE,   0x1},
        {"SW",    &SWExec,    Opcode::STORE,   0x2},
        {"ADDI",  &ADDIExec,  Opcode::OP_IMM},
        {"SLTI",  &SLTIExec,  Opcode::OP_IMM, 0x2},
        {"SLTIU", &SLTIUExec, Opcode::OP_IMM, 0x3},
        {"XORI",  &XORIExec,  Opcode::OP_IMM, 0x4},
        {"ORI",   &ORIExec,   Opcode::OP_IMM, 0x6},
        {"ANDI",  &ANDIExec,  Opcode::OP_IMM, 0x7},
        {"SLLI",  &SLLIExec,  Opcode::OP_IMM, 0x1},
        {"SRLI",  &SRLIExec,  Opcode::OP_IMM, 0x5},
        {"SRAI",  &SRAIExec,  Opcode::OP_IMM, 0x5, 0x20},
        {"ADD",   &ADDExec,   Opcode::OP},
        {"SUB",   &SUBExec,   Opcode::OP,      0x0, 0x20},
        {"SLL",   &SLLExec,   Opcode::OP,      0x1},
        {"SLT",   &SLTExec,   Opcode::OP,      0x2},
        {"SLTU",  &SLTUExec,  Opcode::OP,      0x3},
        {"XOR",   &XORExec,   Opcode::OP,      0x4},
        {"SRL",   &SRLExec,   Opcode::OP,      0x5},
        {"SRA",   &SRAExec,   Opcode::OP,      0x5, 0x20},
        {"OR",    &ORExec,    Opcode::OP,      0x6},
        {"AND",   &ANDExec,   Opcode::OP,      0x7},
        {"ECALL", &ECALLExec, Opcode::SYSTEM},
        {"CSRRW", &CSRRWExec, Opcode::SYSTEM,  0x1},
        {"CSRRS", &CSRRSExec, Opcode::SYSTEM,  0x2},
        {"CSRRC", &CSRRCExec, Opcode::SYSTEM,  0x3},
        {"CSRRWI",&CSRRWIExec,Opcode::SYSTEM,  0x5},
        {"CSRRSI",&CSRRSIExec,Opcode::SYSTEM,  0x6},
        {"CSRRCI",&CSRRCIExec,Opcode::SYSTEM,  0x7},
        {"MUL",   &MULExec,   Opcode::OP,      0x0, 0x1},
        {"MULH",  &MULHExec,  Opcode::OP,      0x1, 0x1},
        {"MULHSU",&MULHSUExec,Opcode::OP,      0x2, 0x1},
        {"MULHU", &MULHUExec, Opcode::OP,      0x3, 0x1},
        {"DIV",   &DIVExec,   Opcode::OP,      0x4, 0x1},
        {"DIVU",  &DIVUExec,  Opcode::OP,      0x5, 0x1},
        {"REM",   &REMExec,   Opcode::OP,      0x6, 0x1},
        {"REMU",  &REMUExec,  Opcode::OP,      0x7, 0x1},
        {"BBEN",  &BBENDExec, Opcode::LOAD}
};


class Decoder {
private:
    std::unordered_map <uint16_t, Command> orderedCommandList;
    uint16_t size = sizeof(commandList) / sizeof(Command);
public:
    Decoder();

    ~Decoder(){}

    Instruction Decode(uint32_t instr);
};
