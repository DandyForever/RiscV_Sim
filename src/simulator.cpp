#include "simulator.h"

void Simulator::Execute() {
    Instruction instr;
    try {
        uint32_t addr = 0;
        uint32_t* raw_instr_;
        uint32_t raw_instr;
        while (true) {
            addr = machine_state.GetPC();
            raw_instr_ = IC.get(addr);
            if (!instr_) {
                raw_instr = machine_state.Fetch(addr);
                IC.put(addr, raw_instr);
            }
            raw_instr = *raw_instr_;
            instr = decoder.decode(raw_instr);
            instr.Exec(machine_state);
        }
    } catch (EndException& e) {
        std::cout << exc.what() << std::endl;
    } catch (SimpleException& e) {
        std::cout << exc.what() << std::endl;
    } catch (ComputeException& e) {
        std::cout << exc.what() << std::endl;
    } catch (RegisterException& e) {
        std::cout << exc.what() << std::endl;
    } catch (OutOfMemoryException& e) {
        std::cout << exc.what() << std::endl;
    } catch (UnalignException& e) {
        std::cout << exc.what() << std::endl;
    } catch (PageFaultException& e) {
        std::cout << exc.what() << std::endl;
    }
}
