#include "decoder.h"

Instruction Decoder::Decode(uint32_t byte_instr) {
    Instruction instr = Instruction();
    uint8_t opcode = 0x7F & byte_instr;
    uint32_t rd_init = (0xF80 & byte_instr) >> 7;

    if ((0x14 & opcode) == 0x14) {
        if (rd_init == 0)
            instr.SetRd(32);
        else
            instr.SetRd(rd_init);
        instr.SetImm((0xFFFFF000 & byte_instr) >> 12);
        if (instr.GetImm() & 0x80000)
            instr.SetImm(instr.GetImm() | 0xFFF00000);
    } else if (opcode == 0x6F) {
        if (rd_init == 0)
            instr.SetRd(32);
        else
            instr.SetRd(rd_init);
        instr.SetImm((0x7FE00000 & byte_instr) >> 21);
        instr.SetImm(instr.GetImm() | (0x100000 & byte_instr) >> 10);
        instr.SetImm(instr.GetImm() | (0xFF000 & byte_instr) >> 1);
        instr.SetImm(instr.GetImm() | (0x80000000 & byte_instr) >> 12);
        if (0x80000000 & byte_instr)
            instr.SetImm(instr.GetImm() | 0xFFF00000);
    } else if (opcode == 0x33) {
        if (rd_init == 0)
            instr.SetRd(32);
        else
            instr.SetRd(rd_init);
        instr.SetFunct3((0x7000 & byte_instr) >> 12);
        instr.SetRs1((0xF8000 & byte_instr) >> 15);
        instr.SetRs2((0x1F00000 & byte_instr) >> 20);
        instr.SetFunct7((0xFE000000 & byte_instr) >> 25);
    } else if (opcode == 0x3 || opcode == 0x13 ||
               opcode == 0x73 || opcode == 0x67) {
        if (rd_init == 0)
            instr.SetRd(32);
        else
            instr.SetRd(rd_init);
        instr.SetFunct3((0x7000 & byte_instr) >> 12);
        instr.SetRs1((0xF8000 & byte_instr) >> 15);
        instr.SetImm((0xFFF00000 & byte_instr) >> 20);
        if (instr.GetImm() & 0x800)
            instr.SetImm(instr.GetImm() | 0xFFFFF000);
    } else if (opcode == 0x23) {
        instr.SetFunct3((0x7000 & byte_instr) >> 12);
        instr.SetRs1((0xF8000 & byte_instr) >> 15);
        instr.SetRs2((0x1F00000 & byte_instr) >> 20);
        instr.SetImm((0xF80 & byte_instr) >> 7);
        instr.SetImm(instr.GetImm() | (0xFE000000 & byte_instr) >> 20);
        if (instr.GetImm() & 0x800)
            instr.SetImm(instr.GetImm() | 0xFFFFF000);
    } else if (opcode == 0x63) {
        instr.SetFunct3((0x7000 & byte_instr) >> 12);
        instr.SetRs1((0xF8000 & byte_instr) >> 15);
        instr.SetRs2((0x1F00000 & byte_instr) >> 20);
        instr.SetImm((0xF00 & byte_instr) >> 8);
        instr.SetImm(instr.GetImm() | (0x7E000000 & byte_instr) >> 21);
        instr.SetImm(instr.GetImm() | (0x80 & byte_instr) << 3);
        instr.SetImm(instr.GetImm() | (0x80000000 & byte_instr) >> 20);
        if (instr.GetImm() & 0x800)
            instr.SetImm(instr.GetImm() | 0xFFFFF000);
    }

    uint16_t hash = instr.GetHash(opcode);
    instr.SetCommand(orderedCommandList[hash].name, orderedCommandList[hash].cmd);

    return instr;
}

Decoder::Decoder() {
    uint16_t hash = 0;
    orderedCommandList[0] = commandList[size - 1];
    for (int i = 0; i < size - 1; i++) {
        hash = (static_cast<uint8_t>(commandList[i].opcode) >> 2) | (commandList[i].funct3 << 5) |
               (commandList[i].funct7 << 8);
        orderedCommandList[hash] = commandList[i];
    }
}
