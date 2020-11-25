#include "decoder.hpp"

Instruction Decoder::Decode(uint32_t byte_instr) {
    Instruction instruction = Instruction();
    uint8_t opcode = 0x7F & byte_instr;

    if ((0x14 & opcode) == 0x14) {
        instr.SetImm((0xFFFFF000 & raw_instr) >> 12);
        if (instr.GetImm() & 0x80000)
            instr.SetImm(instr.GetImm() | 0xFFF00000);
    } else if (opcode == 0x6F){
        instr.SetRd((0xF80 & byte_instr) >> 7);
        instr.SetImm((0x7FE00000 & raw_instr) >> 21);
        instr.SetImm(instr.GetImm() | (0x100000 & raw_instr) >> 10);
        instr.SetImm(instr.GetImm() | (0xFF000 & raw_instr));
        instr.SetImm(instr.GetImm() | (0x80000000 & raw_instr) >> 12);
        if (0x80000000 & byte_instr)
            instr.SetImm(instr.GetImm() | 0xFFF00000);
    } else if (opcode == 0x33) {
        instr.SetRd((0xF80 & byte_instr) >> 7);
        instr.SetFunct3((0x7000 & byte_instr) >> 12);
        instr.SetRs1((0xF8000 & byte_instr) >> 15);
        instr.SetRs2((0x1F00000 & byte_instr) >> 20);
        instr.SetFunct7((0xFE000000 & byte_instr) >> 25);
    } else if (opcode == 0x3 || opcode == 0x13 ||
               opcode == 0x73 || opcode == 0x67) {
        instr.SetRd((0xF80 & byte_instr) >> 7);
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
            instr.SetImm (instr.GetImm() | 0xFFFFF000);
    } else if (opcode == 0x63) {
        instr.SetFunct3((0x7000 & raw_instr) >> 12);
        instr.SetRs1((0xF8000 & raw_instr) >> 15);
        instr.SetRs2((0x1F00000 & raw_instr) >> 20);
        instr.SetImm((0xF00 & raw_instr) >> 8);
        instr.SetImm(instr.GetImm() | (0x7E000000 & raw_instr) >> 21);
        instr.SetImm(instr.GetImm() | (0x80 & raw_instr) << 3);
        instr.SetImm(instr.GetImm() | (0x80000000 & raw_instr) >> 20);
        if (instr.GetImm() & 0x800)
            instr.SetImm (instr.GetImm() | 0xFFFFF000);
    }

    uint16_t hash = instr.GetHash();
    instr.SetCommand(ordered_Command_List[hash].name, ordered_Command_List[hash].cmd);

    return instr;
}

Decoder::Decoder() {
    uint16_t hash = 0;
    SortedCommands[0] = CommandList[size - 1];
    for (unsigned int i = 0; i < size - 1; i++) {
        hash = (static_cast<uint8_t>(CommandList[i].opcode) >> 2) | (CommandList[i].funct3 << 5) | (CommandList[i].funct7 << 8);
        SortedCommands[hash] = CommandList[i];
    }
}