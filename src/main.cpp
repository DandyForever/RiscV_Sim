#include "elf_manager.h"
#include "decoder.h"
#include "exception.h"
#include "simulator.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    ElfManager ER(argv[1]);
    uint32_t PC = 0;
    std::vector<uint32_t> instr(ER.getWords());
    std::cout << "I have read the words form ELF file" << std::endl;

    PC = ER.getPC();
    uint32_t num_pages = 24;
    MachineState state(PC, instr, num_pages);
    std::cout << "I initialized machine state" << std::endl;
    Simulator simulator = Simulator(state);
    std::cout << "I initialized simulator" << std::endl;
    simulator.Execute();
    std::cout << "I executed all instructions " << std::dec << state.GetCmdCount() << std::endl;
    
    /*Decoder DCD = Decoder ();
    Instruction decoded_instr = Instruction ();
    bool is_verbose = true;
    try
    {
        while (true)
        {
            decoded_instr = DCD.Decode(state.ReadWord(state.GetPC()));
            decoded_instr.PrintInstr(is_verbose);
            decoded_instr.Exec(&state);
        }
    }
    catch (MachineException &exc)
    {
        printf ("%s", exc.what());
    }
    //state.MemDump();*/
    return 0;
}
