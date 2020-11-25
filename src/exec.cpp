#include "exec.h"

#define PC_next state->SetPc(state->GetPc() + 4)

void ADDIExec   (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) + static_cast<int32_t>(instr->GetImm())); 
    PC_next;
}

void SLTIExec   (const Instruction* instr, MachineState* state) {
    (int32_t)state->GetReg(instr->GetRs1()) < (int32_t)instr->GetImm() ? state->SetReg(instr->GetRd(), 1) : state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void SLTIUExec  (const Instruction* instr, MachineState* state) {
    state->GetReg(instr->GetRs1()) < instr->GetImm() ? state->SetReg(instr->GetRd(), 1) : state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void XORIExec   (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) ^ instr->GetImm());
    PC_next;
}

void ORIExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) | instr->GetImm());
    PC_next;
}

void ANDIExec   (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) & instr->GetImm());
    PC_next;
}

void SBExec     (const Instruction* instr, MachineState* state) {
    state->WriteByte (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_next;
}

void SHExec     (const Instruction* instr, MachineState* state) {
    state->WriteHalfWord (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_next;
}

void SWExec     (const Instruction* instr, MachineState* state) {
    state->WriteWord (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_next;
}

void LBExec     (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast<int32_t>(static_cast<int8_t>(state->ReadByte (instr->GetImm() + state->GetReg(instr->GetRs1())))));
    PC_next;
}

void LHExec     (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast<int32_t>(static_cast<int16_t>(state->ReadHalfWord (instr->GetImm() + state->GetReg(instr->GetRs1())))));
    PC_next;
}

void LWExec     (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast<int32_t>(state->ReadWord (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_next;
}

void LBUExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast <uint32_t>(state->ReadByte (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_next;
}

void LHUExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast <uint32_t>(state->ReadHalfWord (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_next;
}


void LUIExec    (const Instruction* instr, MachineState* state) {
    state->SetReg (instr->GetRd(), (instr->GetImm()) << 12);
    PC_next;
}

void AUIPCExec  (const Instruction* instr, MachineState* state) {
    state->SetReg (instr->GetRd(), (instr->GetImm() << 12) + state->GetPc());
    PC_next;
}

void BEQExec    (const Instruction* instr, MachineState* state) {
    state->GetReg(instr->GetRs1()) == state->GetReg(instr->GetRs2()) ? 
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : PC_next;
}

void BNEExec    (const Instruction* instr, MachineState* state) {
    state->GetReg(instr->GetRs1()) != state->GetReg(instr->GetRs2()) ?
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : PC_next; 
}

void BLTExec    (const Instruction* instr, MachineState* state) {
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) < static_cast<int32_t>(state->GetReg(instr->GetRs2())) ?
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : PC_next; 
}

void BGEExec    (const Instruction* instr, MachineState* state) {
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) >= static_cast<int32_t>(state->GetReg(instr->GetRs2())) ? 
    state->SetPc(state->GetPc() + (static_cast<int32_t>(instr->GetImm()) << 1)) : PC_next; 
}

void BLTUExec   (const Instruction* instr, MachineState* state) {
    state->GetReg(instr->GetRs1()) < state->GetReg(instr->GetRs2()) ? 
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : PC_next; 
}

void BGEUExec   (const Instruction* instr, MachineState* state) {
    state->GetReg(instr->GetRs1()) > state->GetReg(instr->GetRs2()) ?
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : PC_next; 
}

void JALExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetPc() + 4);
    state->SetPc(state->GetPc() + (static_cast<int32_t>(instr->GetImm()) << 1));
}

void JALRExec   (const Instruction* instr, MachineState* state) {
   state->SetReg(instr->GetRd(), state->GetPc() + 4);
   state->SetPc(state->GetPc() + ((instr->GetRs1() + static_cast<int32_t>(instr->GetImm())) & 0xFFFFFFFE));  
   if (instr->GetOppcode() == 0x67 && instr->GetRs1() == 1 && instr->GetRd() == 0)
       throw MachineException("Jumping to return address\n");
}

void SLLIExec   (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), instr->GetRs1() << (instr->GetImm() & 0x1F));
    PC_next;
}

void SRLIExec   (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), instr->GetRs1() >> (instr->GetImm() & 0x1F));
    PC_next;
}

void SRAIExec   (const Instruction* instr, MachineState* state) {
    uint32_t sb_copy = static_cast<int32_t>(instr->GetImm()) < 0 ? ~(~0u >> instr->GetImm()) : 0;
    state->SetReg(instr->GetRd(), (state->GetReg(instr->GetRs1()) >> instr->GetImm()) | sb_copy);
    PC_next;
}

void ADDExec   (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) + state->GetReg(instr->GetRs2()));
    PC_next;
}

void SUBExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) - state->GetReg(instr->GetRs2()));
    PC_next;
}

void SLLExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) << state->GetReg(instr->GetRs2()));
    PC_next;
}

void SLTExec    (const Instruction* instr, MachineState* state) {
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) < static_cast<int32_t>(state->GetReg(instr->GetRs2())) ? 
    state->SetReg(instr->GetRd(), 1):
    state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void SLTUExec   (const Instruction* instr, MachineState* state) {
    state->GetReg(instr->GetRs1()) < state->GetReg(instr->GetRs2()) ? 
    state->SetReg(instr->GetRd(), 1):
    state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void XORExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) ^ state->GetReg(instr->GetRs2()));
    PC_next;
}

void SRLExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) >> (state->GetReg(instr->GetRs2()) & 0x1F));
    PC_next;
}

void SRAExec    (const Instruction* instr, MachineState* state) {
    uint8_t offs = state->GetReg(instr->GetRs2()) & 0x1F;
    uint32_t sb_copy = static_cast<int8_t>(instr->GetRs1()) < 0 ? ~(~0xFFFFFFFF >> offs) : 0; 
    state->SetReg(instr->GetRd(), (state->GetReg(instr->GetRs1()) >> offs) | sb_copy);
    PC_next;
}

void ORExec     (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) | state->GetReg(instr->GetRs2()));
    PC_next;
}

void ANDExec    (const Instruction* instr, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) & state->GetReg(instr->GetRs2()));
    PC_next;
}

void DUMMYExec  (const Instruction* instr, MachineState* state) {
    printf ("Empty instruction");
}

void ECALLExec  (const Instruction* instr, MachineState* state) {
    throw MachineException ("Finished execution!\n");
}
