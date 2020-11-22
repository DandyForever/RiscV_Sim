#include <iostream>
#include "../../src/elf_manager.h"

int main(int argc, char* argv[]) {
    if (argc != 2)
        errx(EXIT_FAILURE, "Miss arg: name of ELF file");
    ElfManager em(argv[1]);
    auto PC = em.getPC();
    auto words = em.getWords();
    std::cout << PC << std::endl;
    for (size_t i = 0; i < words.size(); i++) {
        std::cout << std::hex << words[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
