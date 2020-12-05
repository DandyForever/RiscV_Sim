#pragma once
#include "machine_state.h"
#include "decoder.h"
#include "cache.h"

class Simulator{
public:
    Sim(MachineState& state): IC(), machine_state(state) {}
    ~Sim();

    void Execute();

private:
    Cache<uint32_t> IC;
    MachineState machine_state;
    Decoder decoder;
};
