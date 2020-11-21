class MMU {
public:
    MMU();
    ~MMU();

    void WriteWordPhysAddr(uint64_t pa, uint32_t data);
    void WriteWordVirtAddr(uint32_t va, uint32_t data);

    uint32_t ReadWordPhysAddr(uint64_t pa);
    uint32_t ReadWordVirtAddr(uint32_t va);

    uint32_t Fetch(uint32_t va);

    uint64_t Translate(uint32_t va);
};
