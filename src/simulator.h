#pragma once
#include "machine_state.h"
#include "decoder.h"
#include "cache.h"
#include "basic_block.h"
#include <chrono>

class Simulator{
public:
    Simulator(MachineState& state): IC(), machine_state(state) {}
    ~Simulator() {}

    void Execute();
    
private:
    Cache<BasicBlock> IC;
    MachineState& machine_state;
    Decoder decoder;
};

