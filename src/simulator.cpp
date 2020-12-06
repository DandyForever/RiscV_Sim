#include "simulator.h"

void Simulator::Execute() {
    Instruction instr;
    try {
        uint32_t addr = 0;
        uint32_t* raw_instr_;
        uint32_t raw_instr;
        while (true) {
            addr = machine_state.GetPC();
            std::cout << "Trying to read from IC " << std::dec << machine_state.GetCmdCount() << std::endl;
            raw_instr_ = IC.get(addr);
            if (!raw_instr_) {
                std::cout << "Trying to fetch the instruction" << std::endl;
                raw_instr = machine_state.Fetch(addr);
                std::cout << "Putting fetched instruction to IC" << std::endl;
                IC.put(addr, raw_instr);
            } else {
                std::cout << "Trying to depointer raw_instr" << std::endl;
                raw_instr = *raw_instr_;
            }
            std::cout << "raw instruction is ready and it is " << std::hex << raw_instr << std::endl;
            instr = decoder.Decode(raw_instr);
            std::cout << "decoded instruction is " << std::endl << std::endl;
            instr.PrintInstr(true);
            std::cout << std::endl;
            instr.Exec(&machine_state);
            machine_state.DumpRegs();
            machine_state.IncreaseCmdCount();
        }
    } catch (EndException& e) {
        std::cout << e.what() << std::endl;
    } catch (SimpleException& e) {
        std::cout << e.what() << std::endl;
    } catch (ComputeException& e) {
        std::cout << e.what() << std::endl;
    } catch (RegisterException& e) {
        std::cout << e.what() << std::endl;
    } catch (OutOfMemoryException& e) {
        std::cout << e.what() << std::endl;
    } catch (UnalignException& e) {
        std::cout << e.what() << std::endl;
    } catch (PageFaultException& e) {
        std::cout << e.what() << std::endl;
    }
}
