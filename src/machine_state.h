class MachineState{
public:
    MachineState();
    ~MachineState();

    void SetPC(uint32_t value);
    void SetReg(uint8_t num, uint32_t value);
    
    uint32_t GetPC();
    uint32_t GetReg(uint8_t num);

    void WriteWord(uint32_t va, uint32_t data);
    uint32_t ReadWord(uint32_t va);

    uint32_t Fetch(uint32_t va);

private:
    uint32_t pc;
    uint32_t reg[33];
    MMU mmu;
};
