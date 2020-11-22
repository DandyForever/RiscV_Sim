#include "elf_manager.h"
#include <algorithm>

int check_input(const char* file_name) {
    if (elf_version(EV_CURRENT) == EV_NONE)
        errx(EXIT_FAILURE, "ELF lib failed: %s", elf_errmsg(-1));
    auto fd = open(file_name, O_RDONLY, 0);
    if (fd < 0)
        err(EXIT_FAILURE, "Can't open input file");
    return fd;
}

Elf* check_elf(int fd) {
    Elf* elf = elf_begin(fd, ELF_C_READ, NULL);
    if (elf == NULL)
        errx(EXIT_FAILURE, "elf_begin failed: %s", elf_errmsg(-1));
    if (elf_kind(elf) != ELF_K_ELF)
        errx(EXIT_FAILURE, "input file is not ELF file");
    return elf;
}

uint32_t read_pc(Elf* elf) {
    GElf_Ehdr ehdr;
    if (gelf_getehdr(elf, &ehdr) == NULL)
        errx(EXIT_FAILURE, "gelf_getehdr failed: %s", elf_errmsg(-1));
    if (ehdr.e_machine != EM_RISCV)
        errx(EXIT_FAILURE, "input file is not for RISC-V machine");
    if (ehdr.e_ident[EI_CLASS] != ELFCLASS32)
        errx(EXIT_FAILURE, "input file is not for 32 bit machine");
    return ehdr.e_entry;
}


uint32_t read_phdrnum(Elf* elf) {
    size_t phdr_num = 0;
    if (elf_getphdrnum(elf, &phdr_num) != 0)
        errx(EXIT_FAILURE, "elf_getphdrnum failed: %s", elf_errmsg(-1));
    return phdr_num;
}

void ElfManager::read_phdrs(Elf* elf, size_t phdr_num) {
    phdrs.resize(phdr_num);
    GElf_Phdr phdr;
    for (size_t i = 0; i < phdr_num; i++) {
        if (gelf_getphdr(elf, i, &phdr) != &phdr)
            errx(EXIT_FAILURE, "getphdr failure: %s", elf_errmsg(-1));
        phdrs[i] = phdr;
    }
}

size_t read_words_num(std::vector<GElf_Phdr>& phdrs) {
    auto best = *std::max_element(phdrs.begin(), phdrs.end(), [](GElf_Phdr a, GElf_Phdr b){ return a.p_vaddr + a.p_memsz < b.p_vaddr + b.p_memsz; });
    return best.p_vaddr + best.p_memsz;
}

void ElfManager::read_words(int fd) {
    words.resize(read_words_num(phdrs) / sizeof(uint32_t));
    for (size_t i = 0; i < phdrs.size(); i++) {
        std::vector<uint32_t> current(phdrs[i].p_memsz);
        lseek(fd, phdrs[i].p_offset, SEEK_SET);
        if (read(fd, &(current[0]), phdrs[i].p_filesz) < 0)
            errx(EXIT_FAILURE, "read failed: %s", elf_errmsg(-1));
        words.insert(words.begin() + phdrs[i].p_paddr / sizeof(uint32_t), current.begin(), current.end());
    }
}

ElfManager::ElfManager(const char* file_name) {
    auto fd = check_input(file_name);
    auto elf = check_elf(fd);
    PC = read_pc(elf);
    auto phdr_num = read_phdrnum(elf);
    read_phdrs(elf, phdr_num);
    read_words(fd);
    elf_end(elf);
    close(fd);
}
