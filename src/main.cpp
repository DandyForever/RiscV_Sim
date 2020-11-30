#include "elf_manager.h"
#include "decoder.h"
#include "exception.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    ElfManager ER(argv[1]);
    uint32_t PC = 0;
    std::vector<uint32_t> instr(ER.getWords());

    PC = ER.getPC();
    MachineState state(PC, instr);
    
    Decoder DCD = Decoder ();
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
    //state.MemDump();
    return 0;
}
