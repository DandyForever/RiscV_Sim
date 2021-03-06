#include "elf_manager.h"
#include "decoder.h"
#include "exception.h"
#include "simulator.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Argument was not found" << std::endl;
        return 1;
    }
    ElfManager ER(argv[1]);
    uint32_t PC = 0;
    std::vector<uint32_t> instr(ER.getWords());
    PC = ER.getPC();
    uint32_t num_pages = 32;
    MachineState state(PC, instr, num_pages);
    Simulator simulator = Simulator(state);
    simulator.Execute();
    return 0;
}
