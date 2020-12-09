#include "simulator.h"

void Simulator::Execute() {
    Instruction instr;
    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
    try {
        uint32_t addr = 0;
        BasicBlock* bb_;
        BasicBlock bb;
        while (true) {
            addr = machine_state.GetPC();
            bb_ = IC.get(addr);
            if (!bb_) {
                bb = BasicBlock(machine_state, decoder);
                bb_ = &bb;
                IC.put(addr, bb);
            }
            bb_->Execute(machine_state);
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
    }/* catch (PageFaultException& e) {
        std::cout << e.what() << std::endl;
    }*/
    std::cout << "I executed all instructions " << std::dec << machine_state.GetCmdCount() << std::endl;
    std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ex_time = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    std::cout << "Execution time is " << ex_time.count() << std::endl; 
    std::cout << "Simulator performance is " << machine_state.GetCmdCount() / ex_time.count() / 1000000 << " MIPS" << std::endl;
}
