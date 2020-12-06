#include "exec.h"

#define PC_next { (instr + 1)->Exec(first, state); }

void ADDIExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) + static_cast<int32_t>(instr->GetImm()));
    PC_next;
}

void SLTIExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    (int32_t)state->GetReg(instr->GetRs1()) < (int32_t)instr->GetImm() ? state->SetReg(instr->GetRd(), 1) : state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void SLTIUExec  (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->GetReg(instr->GetRs1()) < instr->GetImm() ? state->SetReg(instr->GetRd(), 1) : state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void XORIExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) ^ instr->GetImm());
    PC_next;
}

void ORIExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) | instr->GetImm());
    PC_next;
}

void ANDIExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) & instr->GetImm());
    PC_next;
}

void SBExec     (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->WriteByte (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_next;
}

void SHExec     (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->WriteHalfWord (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_next;
}

void SWExec     (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->WriteWord (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_next;
}

void LBExec     (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast<int32_t>(static_cast<int8_t>(state->ReadByte (instr->GetImm() + state->GetReg(instr->GetRs1())))));
    PC_next;
}

void LHExec     (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast<int32_t>(static_cast<int16_t>(state->ReadHalfWord (instr->GetImm() + state->GetReg(instr->GetRs1())))));
    PC_next;
}

void LWExec     (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast<int32_t>(state->ReadWord (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_next;
}

void LBUExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast <uint32_t>(state->ReadByte (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_next;
}

void LHUExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), static_cast <uint32_t>(state->ReadHalfWord (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_next;
}


void LUIExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg (instr->GetRd(), (instr->GetImm()) << 12);
    PC_next;
}

void AUIPCExec  (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg (instr->GetRd(), (instr->GetImm() << 12) + state->GetPC());
    PC_next;
}

void BEQExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->GetReg(instr->GetRs1()) == state->GetReg(instr->GetRs2()) ? 
    state->SetPC(state->GetPC() + (instr - first) * 4 + (instr->GetImm() << 1)) :
    state->SetPC(state->GetPC() + (instr - first + 1) * 4);
    state->IncreaseCmdCount(instr - first + 1);
}

void BNEExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->GetReg(instr->GetRs1()) != state->GetReg(instr->GetRs2()) ?
    state->SetPC(state->GetPC() + (instr - first) * 4 + (instr->GetImm() << 1)) : 
    state->SetPC(state->GetPC() + (instr - first + 1) * 4);
    state->IncreaseCmdCount(instr - first + 1);
     
}

void BLTExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) < static_cast<int32_t>(state->GetReg(instr->GetRs2())) ?
    state->SetPC(state->GetPC() + (instr - first) * 4 + (instr->GetImm() << 1)) : 
    state->SetPC(state->GetPC() + (instr - first + 1) * 4);
    state->IncreaseCmdCount(instr - first + 1);
}

void BGEExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) >= static_cast<int32_t>(state->GetReg(instr->GetRs2())) ? 
    state->SetPC(state->GetPC() + (instr - first) * 4 + (static_cast<int32_t>(instr->GetImm()) << 1)) :
    state->SetPC(state->GetPC() + (instr - first + 1) * 4);
    state->IncreaseCmdCount(instr - first + 1);
}

void BLTUExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->GetReg(instr->GetRs1()) < state->GetReg(instr->GetRs2()) ? 
    state->SetPC(state->GetPC() + (instr - first) * 4 + (instr->GetImm() << 1)) :
    state->SetPC(state->GetPC() + (instr - first + 1) * 4);
    state->IncreaseCmdCount(instr - first + 1);
}

void BGEUExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->GetReg(instr->GetRs1()) > state->GetReg(instr->GetRs2()) ?
    state->SetPC(state->GetPC() + (instr - first) * 4 + (instr->GetImm() << 1)) :
    state->SetPC(state->GetPC() + (instr - first + 1) * 4);
    state->IncreaseCmdCount(instr - first + 1);
}

void JALExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetPC() + (instr - first) * 4 + 4);
    state->SetPC(state->GetPC() + (instr - first) * 4 + (static_cast<int32_t>(instr->GetImm()) << 1));
    state->IncreaseCmdCount(instr - first + 1);
}

void JALRExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    //std::cout << state->GetPC() << " before" << std::endl;
    //state->DumpRegs();
   state->SetReg(instr->GetRd(), state->GetPC() + (instr - first) * 4 + 4);
   state->SetPC(((state->GetReg(instr->GetRs1()) + static_cast<int32_t>(instr->GetImm())) & 0xFFFFFFFE));
    //std::cout << state->GetPC() << " after" << std::endl;
    state->IncreaseCmdCount(instr - first + 1);
}

void SLLIExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) << (instr->GetImm() & 0x1F));
    PC_next;
}

void SRLIExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) >> (instr->GetImm() & 0x1F));
    PC_next;
}

void SRAIExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    uint32_t sb_copy = static_cast<int32_t>(instr->GetImm()) < 0 ? ~(~0u >> instr->GetImm()) : 0;
    state->SetReg(instr->GetRd(), (state->GetReg(instr->GetRs1()) >> instr->GetImm()) | sb_copy);
    PC_next;
}

void ADDExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) + state->GetReg(instr->GetRs2()));
    PC_next;
}

void SUBExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) - state->GetReg(instr->GetRs2()));
    PC_next;
}

void SLLExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) << state->GetReg(instr->GetRs2()));
    PC_next;
}

void SLTExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) < static_cast<int32_t>(state->GetReg(instr->GetRs2())) ?
    state->SetReg(instr->GetRd(), 1):
    state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void SLTUExec   (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->GetReg(instr->GetRs1()) < state->GetReg(instr->GetRs2()) ?
    state->SetReg(instr->GetRd(), 1):
    state->SetReg(instr->GetRd(), 0);
    PC_next;
}

void XORExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) ^ state->GetReg(instr->GetRs2()));
    PC_next;
}

void SRLExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) >> (state->GetReg(instr->GetRs2()) & 0x1F));
    PC_next;
}

void SRAExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    uint8_t offs = state->GetReg(instr->GetRs2()) & 0x1F;
    uint32_t sb_copy = static_cast<int8_t>(state->GetReg(instr->GetRs1())) < 0 ? ~(~0xFFFFFFFF >> offs) : 0;
    state->SetReg(instr->GetRd(), (state->GetReg(instr->GetRs1()) >> offs) | sb_copy);
    PC_next;
}

void ORExec     (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) | state->GetReg(instr->GetRs2()));
    PC_next;
}

void ANDExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) & state->GetReg(instr->GetRs2()));
    PC_next;
}

void DUMMYExec  (const Instruction* instr, const Instruction* first, MachineState* state) {
    printf ("Empty instruction");
}

void ECALLExec  (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->IncreaseCmdCount(instr - first + 1);
    throw EndException ("Finished execution!\n");
}


void MULExec    (const Instruction* instr, const Instruction* first, MachineState* state) {
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) * state->GetReg(instr->GetRs2()));
    PC_next;
}

void MULHExec   (const Instruction* instr, const Instruction* first, MachineState* state)
{
    state->SetReg(instr->GetRd(), ((static_cast<int64_t>(state->GetReg(instr->GetRs1())) * static_cast<int64_t>(state->GetReg(instr->GetRs1())))) >> 32);
    PC_next;
}

void MULHSUExec (const Instruction* instr, const Instruction* first, MachineState* state)
{
    state->SetReg(instr->GetRd(), ((static_cast<int64_t>(state->GetReg(instr->GetRs1())) * static_cast<uint64_t>(state->GetReg(instr->GetRs2())))) >> 32);
    PC_next;
}

void MULHUExec  (const Instruction* instr, const Instruction* first, MachineState* state)
{
    state->SetReg(instr->GetRd(), (static_cast<uint64_t>(state->GetReg(instr->GetRs1())) * static_cast<uint64_t>(state->GetReg(instr->GetRs2()))) >> 32);
    PC_next;
}

void DIVExec    (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (state->GetReg(instr->GetRs2()) == 0)
        throw ComputeException("Division by zero!\n");
    state->SetReg(instr->GetRd(), static_cast<int32_t>(state->GetReg(instr->GetRs1())) / static_cast<int32_t>(state->GetReg(instr->GetRs2())));
    PC_next;
}

void DIVUExec   (const Instruction* instr, const Instruction* first, MachineState* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs2()) ? state->GetReg(instr->GetRs1()) / state->GetReg(instr->GetRs2()) : UINT32_MAX);
    PC_next;
}

void REMExec    (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (state->GetReg(instr->GetRs2()) == 0)
        state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()));
    state->SetReg(instr->GetRd(), static_cast<int32_t>(state->GetReg(instr->GetRs1())) % static_cast<int32_t>(state->GetReg(instr->GetRs2())));
    PC_next;
}

void REMUExec   (const Instruction* instr, const Instruction* first, MachineState* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs2())? state->GetReg(instr->GetRs1()) % state->GetReg(instr->GetRs2()) : state->GetReg(instr->GetRs1()));
    PC_next;
}

/*void BASICDUMMY (const Instruction* instr, const Instruction* first, MachineState* state)
{
    SET_PC (GET_PC() + (cur_instr - first_instr) * 4);
    CMD_incr(cur_instr - first_instr);
}*/

void CSRRWExec  (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (instr->GetImm() != 0x180)
        throw RegisterException("Only SATP system register is supported!\n");
    state->SetReg(instr->GetRd(), state->GetSatp());
    state->SetSatp(state->GetReg(instr->GetRs1()));
    PC_next;
}

void CSRRSExec  (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (instr->GetImm() != 0x180)
        throw RegisterException("Only SATP system register is supported!\n");
    state->SetReg(instr->GetRd(), state->GetSatp());
    state->SetSatp(state->GetSatp() | state->GetReg(instr->GetRs1()));
    PC_next;
}

void CSRRCExec  (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (instr->GetImm() != 0x180)
        throw RegisterException("Only SATP system register is supported!\n");
    state->SetReg(instr->GetRd(), state->GetSatp());
    state->SetSatp(state->GetSatp() | (!state->GetReg(instr->GetRs1())));
    PC_next;
}

void CSRRWIExec (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (instr->GetImm() != 0x180)
        throw RegisterException("Only SATP system register is supported!\n");
    state->SetReg(instr->GetRd(), state->GetSatp());
    state->SetSatp(static_cast<uint32_t>(instr->GetRs1())); //the uimm is formally in rs1 field of I-TYPE instr
    PC_next;
}

void CSRRSIExec (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (instr->GetImm() != 0x180)
        throw RegisterException("Only SATP system register is supported!\n");
    state->SetReg(instr->GetRd(), state->GetSatp());
    state->SetSatp(state->GetSatp() | static_cast<uint32_t>(instr->GetRs1()));
    PC_next;
}

void CSRRCIExec (const Instruction* instr, const Instruction* first, MachineState* state)
{
    if (instr->GetImm() != 0x180)
        throw RegisterException("Only SATP system register is supported!\n");
    state->SetReg(instr->GetRd(), state->GetSatp());
    state->SetSatp(state->GetSatp() | (!static_cast<uint32_t>(state->GetReg(instr->GetRs1()))));
    PC_next;
}

void BBENDExec (const Instruction* instr, const Instruction* first, MachineState* state)
{
    state->SetPC(state->GetPC() + (instr - first) * 4);
    state->IncreaseCmdCount(instr - first);
}
