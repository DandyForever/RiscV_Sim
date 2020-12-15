#pragma once
#include <cstdlib>
#include "machine_state.h"
#include <stdio.h>
#include "exception.h"
#include "instruction.h"

inline void pf_handler(MachineState* state, uint32_t va) {
    state -> SetStval(va);
}

class Instruction;

void Execute(uint32_t &raw_instr, MachineState *state);

void LUIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void AUIPCExec(const Instruction* instr, const Instruction* first, MachineState* state);

void JALExec(const Instruction* instr, const Instruction* first, MachineState* state);

void JALRExec(const Instruction* instr, const Instruction* first, MachineState* state);

void BEQExec(const Instruction* instr, const Instruction* first, MachineState* state);

void BNEExec(const Instruction* instr, const Instruction* first, MachineState* state);

void BLTExec(const Instruction* instr, const Instruction* first, MachineState* state);

void BGEExec(const Instruction* instr, const Instruction* first, MachineState* state);

void BLTUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void BGEUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void LBExec(const Instruction* instr, const Instruction* first, MachineState* state);

void LHExec(const Instruction* instr, const Instruction* first, MachineState* state);

void LWExec(const Instruction* instr, const Instruction* first, MachineState* state);

void LBUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void LHUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SBExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SHExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SWExec(const Instruction* instr, const Instruction* first, MachineState* state);

void ADDIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SLTIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SLTIUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void XORIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void ORIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void ANDIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SLLIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SRLIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SRAIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void ADDExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SUBExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SLLExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SLTExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SLTUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void XORExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SRLExec(const Instruction* instr, const Instruction* first, MachineState* state);

void SRAExec(const Instruction* instr, const Instruction* first, MachineState* state);

void ORExec(const Instruction* instr, const Instruction* first, MachineState* state);

void ANDExec(const Instruction* instr, const Instruction* first, MachineState* state);

void ECALLExec(const Instruction* instr, const Instruction* first, MachineState* state);

//void DUMMYExec(const Instruction* instr, const Instruction* first, MachineState* state);

void CSRRWExec(const Instruction* instr, const Instruction* first, MachineState* state);

void CSRRSExec(const Instruction* instr, const Instruction* first, MachineState* state);

void CSRRCExec(const Instruction* instr, const Instruction* first, MachineState* state);

void CSRRWIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void CSRRSIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void CSRRCIExec(const Instruction* instr, const Instruction* first, MachineState* state);

void MULExec(const Instruction* instr, const Instruction* first, MachineState* state);

void MULHExec(const Instruction* instr, const Instruction* first, MachineState* state);

void MULHSUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void MULHUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void DIVExec(const Instruction* instr, const Instruction* first, MachineState* state);

void DIVUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void REMExec(const Instruction* instr, const Instruction* first, MachineState* state);

void REMUExec(const Instruction* instr, const Instruction* first, MachineState* state);

void DUMMYExec(const Instruction* instr, const Instruction* first, MachineState* state);

void BBENDExec(const Instruction* instr, const Instruction* first, MachineState* state);
