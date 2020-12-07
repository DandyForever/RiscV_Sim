#include "simulator.h"

void Simulator::Execute() {
    Instruction instr;
    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
    auto bb_start = std::chrono::high_resolution_clock::now();
    auto create_start = std::chrono::high_resolution_clock::now();
    auto bb_end = std::chrono::high_resolution_clock::now();
    auto create_end = std::chrono::high_resolution_clock::now();
    try {
        uint32_t addr = 0;
        BasicBlock* bb_;
        BasicBlock bb;
        while (true) {
            addr = machine_state.GetPC();
            //if (machine_state.GetCmdCount() % 10000 == 0)
            //    std::cout << std::dec << machine_state.GetCmdCount() << "\n";
            bb_ = IC.get(addr);
            create_start = std::chrono::high_resolution_clock::now();
            if (!bb_) {
                //std::cout << "Trying to fetch the instruction" << std::endl;
                bb = BasicBlock(machine_state, decoder);
                IC.put(addr, bb);
                bb_ = &bb;
                //std::cout << "Putting fetched instruction to IC" << std::endl;
                IC.put(addr, bb);
            }
            create_end = std::chrono::high_resolution_clock::now();
            create_time += std::chrono::duration_cast<std::chrono::duration<double>>(create_end - create_start).count();
                //std::cout << "Trying to depointer raw_instr" << std::endl;
            bb_start = std::chrono::high_resolution_clock::now();
            bb_->Execute(machine_state);
            bb_end = std::chrono::high_resolution_clock::now();
            bb_time += std::chrono::duration_cast<std::chrono::duration<double>>(bb_end - bb_start).count();
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
    std::cout << "I executed all instructions " << std::dec << machine_state.GetCmdCount() << std::endl;
    std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ex_time = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    std::cout << "Execution time is " << ex_time.count() << std::endl; 
    std::cout << "Simulator performance is " << machine_state.GetCmdCount() / ex_time.count() / 1000000 << " MIPS" << std::endl;
    std::cout << "Basic Block Execution time is " << bb_time << std::endl; 
    std::cout << "Basic Block Creation time is " << create_time << std::endl; 
}
