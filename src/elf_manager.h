class ElfManager {
public:
    ElfManager(const char* file_name);
    ~ElfManager();

    std::vector<uint32_t> getWords();
    uint32_t getPC();

private:
    
};
