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
    
    double bb_time;
    double create_time;
private:
    Cache<BasicBlock> IC;
    MachineState& machine_state;
    Decoder decoder;
};
