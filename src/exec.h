#pragma once
#include <cstdlib>
#include "machine_state.h"
#include <stdio.h>
#include "exception.h"
#include "instruction.h"

class Instruction;

void Execute(uint32_t &raw_instr, MachineState *state);

void LUIExec(const Instruction *instr, MachineState *state);

void AUIPCExec(const Instruction *instr, MachineState *state);

void JALExec(const Instruction *instr, MachineState *state);

void JALRExec(const Instruction *instr, MachineState *state);

void BEQExec(const Instruction *instr, MachineState *state);

void BNEExec(const Instruction *instr, MachineState *state);

void BLTExec(const Instruction *instr, MachineState *state);

void BGEExec(const Instruction *instr, MachineState *state);

void BLTUExec(const Instruction *instr, MachineState *state);

void BGEUExec(const Instruction *instr, MachineState *state);

void LBExec(const Instruction *instr, MachineState *state);

void LHExec(const Instruction *instr, MachineState *state);

void LWExec(const Instruction *instr, MachineState *state);

void LBUExec(const Instruction *instr, MachineState *state);

void LHUExec(const Instruction *instr, MachineState *state);

void SBExec(const Instruction *instr, MachineState *state);

void SHExec(const Instruction *instr, MachineState *state);

void SWExec(const Instruction *instr, MachineState *state);

void ADDIExec(const Instruction *instr, MachineState *state);

void SLTIExec(const Instruction *instr, MachineState *state);

void SLTIUExec(const Instruction *instr, MachineState *state);

void XORIExec(const Instruction *instr, MachineState *state);

void ORIExec(const Instruction *instr, MachineState *state);

void ANDIExec(const Instruction *instr, MachineState *state);

void SLLIExec(const Instruction *instr, MachineState *state);

void SRLIExec(const Instruction *instr, MachineState *state);

void SRAIExec(const Instruction *instr, MachineState *state);

void ADDExec(const Instruction *instr, MachineState *state);

void SUBExec(const Instruction *instr, MachineState *state);

void SLLExec(const Instruction *instr, MachineState *state);

void SLTExec(const Instruction *instr, MachineState *state);

void SLTUExec(const Instruction *instr, MachineState *state);

void XORExec(const Instruction *instr, MachineState *state);

void SRLExec(const Instruction *instr, MachineState *state);

void SRAExec(const Instruction *instr, MachineState *state);

void ORExec(const Instruction *instr, MachineState *state);

void ANDExec(const Instruction *instr, MachineState *state);

void ECALLExec(const Instruction *instr, MachineState *state);

void DUMMYExec(const Instruction *instr, MachineState *state);

void CSRRWExec(const Instruction *instr, MachineState *state);

void CSRRSExec(const Instruction *instr, MachineState *state);

void CSRRCExec(const Instruction *instr, MachineState *state);

void CSRRWIExec(const Instruction *instr, MachineState *state);

void CSRRSIExec(const Instruction *instr, MachineState *state);

void CSRRCIExec(const Instruction *instr, MachineState *state);

void MULExec(const Instruction *instr, MachineState *state);

void MULHExec(const Instruction *instr, MachineState *state);

void MULHSUExec(const Instruction *instr, MachineState *state);

void MULHUExec(const Instruction *instr, MachineState *state);

void DIVExec(const Instruction *instr, MachineState *state);

void DIVUExec(const Instruction *instr, MachineState *state);

void REMExec(const Instruction *instr, MachineState *state);

void REMUExec(const Instruction *instr, MachineState *state);

void DUMMYExec(const Instruction *instr, MachineState *state);
