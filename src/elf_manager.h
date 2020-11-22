#include <vector>
#include <gelf.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>

class ElfManager {
public:
    ElfManager() = delete;
    ElfManager(const char* file_name);
    ~ElfManager(){}

    std::vector<uint32_t>& getWords() { return words; }
    uint32_t getPC() { return PC; }

private:
    uint32_t PC;
    std::vector<uint32_t> words;
    std::vector<GElf_Phdr> phdrs;

    void read_words(int fd);
    void read_phdrs(Elf* elf, size_t phdr_num);
};
