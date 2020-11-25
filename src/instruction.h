class Instruction {
private:
    uint8_t rd = 0;
    uint8_t funct3 = 0;
    uint8_t rs1 = 0;
    uint8_t rs2 = 0;
    uint8_t funct7 = 0;
    uint32_t imm = 0;

    void (*cmd)(const Instruction *, State *);

    const char *name;
public:
    Instruction();

    uint8_t GetRd() const;

    uint8_t GetFunct3() const;

    uint8_t GetRs1() const;

    uint8_t GetRs2() const;

    uint8_t GetFunct7() const;

    uint16_t GetHash() const;

    uint32_t GetImm() const;

    void Exec(State *state);

    void SetRd(uint8_t rd);

    void SetFunct3(uint8_t funct3);

    void SetRs1(uint8_t rs1);

    void SetRs2(uint8_t rs1);

    void SetFunct7(uint8_t funct7);

    void SetImm(uint32_t imm);

    void SetCommand(const char *name, void (*cmd)(const Instruction *, State *));

    void PrintInstr(const bool is_verbose);
};
