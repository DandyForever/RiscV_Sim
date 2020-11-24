

class MachineState{
public:
    const int regs_num = 32;

    MachineState(uint32_t initial_pc, std::vector<uint32_t>& words);
    ~MachineState() {}

    void SetPC(uint32_t value);
    void SetReg(uint8_t num, uint32_t value);
    
    uint32_t GetPC();
    uint32_t GetReg(uint8_t num);

    void WriteWord(uint32_t va, uint32_t data);
    void WriteHalfWord(uint32_t va, uint16_t data);
    void WriteByte(uint32_t va, uint8_t data);
    uint32_t ReadWord(uint32_t va);
    uint16_t ReadHalfWord(uint32_t va);
    uint8_t ReadByte(uint32_t va);

    //uint32_t Fetch(uint32_t va);

private:
    uint32_t pc;
    uint32_t regs[32];
    //MMU mmu;
    std::vector<uint8_t> memory;
};
