#include "instruction.h"

void Instruction::PrintInstr(const bool is_verbose) {
    if (is_verbose) {
        printf("name   : %s\n", name);
        printf("rd     : %u\n", rd);
        //printf("funct3 : %u\n", funct3);
        printf("rs1    : %u\n", rs1);
        printf("rs2    : %u\n", rs2);
        //printf("funct7 : %u\n", funct7);
        printf("imm    : %x\n\n", imm);
    }
}
