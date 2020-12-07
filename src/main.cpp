#include "elf_manager.h"
#include "decoder.h"
#include "exception.h"
#include "simulator.h"
#include <stdio.h>
#include <chrono>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Argument was not found" << std::endl;
        return 1;
    }
    ElfManager ER(argv[1]);
    uint32_t PC = 0;
    std::vector<uint32_t> instr(ER.getWords());
    //std::cout << "I have read the words form ELF file" << std::endl;
    PC = ER.getPC();
    uint32_t num_pages = 24;
    MachineState state(PC, instr, num_pages);
    //std::cout << "I initialized machine state" << std::endl;
    Simulator simulator = Simulator(state);
    //std::cout << "I initialized simulator" << std::endl;
    simulator.Execute();
    return 0;
}
