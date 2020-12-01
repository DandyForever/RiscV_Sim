#pragma once
#include <vector>
#include <stdint.h>
#include "simple_cache.h"

class MMU {
public:
    enum Access {
        READ,
        WRITE,
        EXEC
    };

    MMU(std::vector<uint32_t>& words, uint32_t num_pages);
    ~MMU() {}

    void SetSatp(uint32_t value) { satp = value; }
    uint32_t GetSatp() { return satp; }

    void WriteWordPhysAddr(uint64_t pa, uint32_t data);
    void WriteWordVirtAddr(uint32_t va, uint32_t data);
    void WriteHalfWordPhysAddr(uint64_t pa, uint16_t data);
    void WriteHalfWordVirtAddr(uint32_t va, uint16_t data);
    void WriteBytePhysAddr(uint64_t pa, uint8_t data);
    void WriteByteVirtAddr(uint32_t va, uint8_t data);

    uint32_t ReadWordPhysAddr(uint64_t pa);
    uint32_t ReadWordVirtAddr(uint32_t va);
    uint32_t ReadHalfWordPhysAddr(uint64_t va);
    uint32_t ReadHalfWordVirtAddr(uint32_t va);
    uint32_t ReadBytePhysAddr(uint64_t va);
    uint32_t ReadByteVirtAddr(uint32_t va);

    uint32_t Fetch(uint32_t va);

    uint64_t Translate(uint32_t va, Access access);

private:
    uint32_t satp;
    std::vector<uint32_t> memory;
    uint64_t max_pa;
    SimpleCache<uint32_t> R_TLB;
    SimpleCache<uint32_t> W_TLB;
    SimpleCache<uint32_t> X_TLB;

    const uint32_t PAGESIZE = 4096;
    const uint32_t LEVELS = 2;
    const uint32_t PTESIZE = 4;
    const uint32_t VBIT = 1 << 0;
    const uint32_t RBIT = 1 << 1;
    const uint32_t WBIT = 1 << 2;
    const uint32_t XBIT = 1 << 3;
    const uint32_t UBIT = 1 << 4;
    const uint32_t GBIT = 1 << 5;
    const uint32_t ABIT = 1 << 6;
    const uint32_t DBIT = 1 << 7;
};
