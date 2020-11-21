class Instruction{
public:
    Instruction();
    ~Instruction();



private:
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    uint32_t immediate;
};
