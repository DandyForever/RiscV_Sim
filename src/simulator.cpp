#include "simulator.h"

void Simulator::Execute() {
    Instruction instr;
    try {
        uint32_t addr = 0;
        BasicBlock* bb_;
        BasicBlock bb;
        while (true) {
            addr = machine_state.GetPC();
            //if (machine_state.GetCmdCount() % 10000 == 0)
            //    std::cout << std::dec << machine_state.GetCmdCount() << "\n";
            bb_ = IC.get(addr);
            if (!bb_) {
                //std::cout << "Trying to fetch the instruction" << std::endl;
                bb = BasicBlock(machine_state, decoder);
                IC.put(addr, bb);
                bb_ = &bb;
                //std::cout << "Putting fetched instruction to IC" << std::endl;
                IC.put(addr, bb);
            }
                //std::cout << "Trying to depointer raw_instr" << std::endl;
            bb_->Execute(machine_state);
            //std::cout << "raw instruction is ready and it is " << std::hex << raw_instr << std::endl;
            //std::cout << "decoded instruction is " << std::endl << std::endl;
            //instr.PrintInstr(true);
            //std::cout << std::endl;
            //machine_state.DumpRegs();
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
