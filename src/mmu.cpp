#include "mmu.h"

MMU::MMU(std::vector<uint32_t>& words, uint32_t num_pages) {
    max_pa = num_pages * PAGESIZE;
    uint64_t max_word = (uint64_t)(words.size() * sizeof(uint32_t));
    if (max_word > max_pa) {
        //std::cout << __func__ << std::endl;
        throw OutOfMemoryException("Address OOM\n", max_word);
    }
    memory.resize(max_pa >> 2);
    memory.insert(memory.begin(), words.begin(), words.end());
    satp = 0x0;
}

void MMU::WriteWordPhysAddr(uint64_t pa, uint32_t data) {
    if (pa + 3 > max_pa) {
        //std::cout << __func__ << std::endl;
        throw OutOfMemoryException("Address OOM\n", pa);
    }
    if ((pa & 0x3) == 0x0)
        memory[pa >> 2] = data;
    else
        throw UnalignException("Address analigned", pa);
}

void MMU::WriteWordVirtAddr(uint32_t va, uint32_t data) {
    uint64_t pa = 0x0;
    uint32_t* ppn;
    if (satp >> 31 == 0)
        pa = (uint64_t) va;
    else {
        ppn = W_TLB.get(va >> 12);
        if (!ppn) {
            pa = Translate(va, WRITE);
            W_TLB.put(va >> 12, pa >> 12);
        } else
            pa = (*ppn << 12) | (va & 0xfff);
    }

    WriteWordPhysAddr(pa, data);
}

void MMU::WriteHalfWordPhysAddr(uint64_t pa, uint16_t data) {
    if (pa + 1 > max_pa) {
        //std::cout << __func__ << std::endl;
        throw OutOfMemoryException("Address OOM\n", pa);
    }
    if ((pa & 0x1) == 0x0) {
        uint32_t offset = (pa & 0x1) * 16;
        memory[pa >> 2] = (memory[pa >> 2] & ~(0xffff << offset)) | ((uint32_t) data << offset);
    } else
        throw UnalignException("Address (%lld) is analigned\n", pa);
}

void MMU::WriteHalfWordVirtAddr(uint32_t va, uint16_t data) {
    uint64_t pa = 0x0;
    uint32_t* ppn;
    if (satp >> 31 == 0)
        pa = (uint64_t) va;
    else {
        ppn = W_TLB.get(va >> 12);
        if (!ppn) {
            pa = Translate(va, WRITE);
            W_TLB.put(va >> 12, pa >> 12);
        } else
            pa = (*ppn << 12) | (va & 0xfff);
    }

    WriteHalfWordPhysAddr(pa, data);
}

void MMU::WriteBytePhysAddr(uint64_t pa, uint8_t data) {
    if (pa > max_pa) {
        //std::cout << __func__ << " " << pa << " "  << max_pa <<  std::endl;
        throw OutOfMemoryException("Address OOM\n", pa);
    }
    uint32_t offset = (pa & 0x3) * 8;
    memory[pa >> 2] = (memory[pa >> 2] & ~(0xff << offset)) | ((uint32_t) data << offset);
}

void MMU::WriteByteVirtAddr(uint32_t va, uint8_t data) {
    uint64_t pa = 0x0;
    uint32_t *ppn;
    if (satp >> 31 == 0)
        pa = (uint64_t) va;
    else {
        ppn = W_TLB.get(va >> 12);
        if (!ppn) {
            pa = Translate(va, WRITE);
            W_TLB.put(va >> 12, pa >> 12);
        } else
            pa = (*ppn << 12) | (va & 0xfff);
    }

    WriteBytePhysAddr(pa, data);
}

uint32_t MMU::ReadWordPhysAddr(uint64_t pa) {
    if (pa + 3 > max_pa) {
        //std::cout << __func__ << std::endl;
        throw OutOfMemoryException("Address OOM\n", pa);
    }
    if ((pa & 0x3) == 0x0)
        return memory[pa >> 2];
    else
        throw UnalignException("Address analigned", pa);
}

uint32_t MMU::ReadWordVirtAddr(uint32_t va) {
    uint64_t pa = 0x0;
    uint32_t* ppn;
    if (satp >> 31 == 0)
        pa = (uint64_t) va;
    else {
        ppn = R_TLB.get(va >> 12);
        if (!ppn) {
            pa = Translate(va, READ);
            R_TLB.put(va >> 12, pa >> 12);
        } else
            pa = (*ppn << 12) | (va & 0xfff);
    }

    return ReadWordPhysAddr(pa);
}

uint16_t MMU::ReadHalfWordPhysAddr(uint64_t pa) {
    if (pa + 1 > max_pa) {
        //std::cout << __func__ << std::endl;
        throw OutOfMemoryException("Address is OOM\n", pa);
    }
    if ((pa & 0x1) == 0x0) {
        uint32_t offset = (pa & 0x1) * 16;
        return (memory[pa >> 2] >> offset) & 0xffff;
    } else
        throw UnalignException("Address is analigned\n", pa);

}

uint16_t MMU::ReadHalfWordVirtAddr(uint32_t va) {
    uint64_t pa = 0x0;
    uint32_t* ppn;
    if (satp >> 31 == 0)
        pa = (uint64_t) va;
    else {
        ppn = R_TLB.get(va >> 12);
        if (!ppn) {
            pa = Translate(va, READ);
            R_TLB.put(va >> 12, pa >> 12);
        } else
            pa = (*ppn << 12) | (va & 0xfff);
    }

    return ReadHalfWordPhysAddr(pa);

}

uint8_t MMU::ReadBytePhysAddr(uint64_t pa) {
    if (pa > max_pa) {
        //std::cout << __func__ << std::endl;
        throw OutOfMemoryException("Address OOM\n", pa);
    }
    uint32_t offset = (pa & 0x3) * 8;
    return (memory[pa >> 2] >> offset) & 0xff;

}
    
uint8_t MMU::ReadByteVirtAddr(uint32_t va) {
    uint64_t pa = 0x0;
    uint32_t *ppn;
    if (satp >> 31 == 0)
        pa = (uint64_t) va;
    else {
        ppn = R_TLB.get(va >> 12);
        if (!ppn) {
            pa = Translate(va, READ);
            R_TLB.put(va >> 12, pa >> 12);
        } else
            pa = (*ppn << 12) | (va & 0xfff);
    }

    return ReadBytePhysAddr(pa);

}

uint32_t MMU::Fetch(uint32_t va) {
    uint64_t pa = 0x0;
    uint32_t* ppn;
    if (satp >> 31 == 0)
        pa = (uint64_t) va;
    else {
        ppn = X_TLB.get(va >> 12);
        if (!ppn) {
            pa = Translate(va, EXEC);
            X_TLB.put(va >> 12, pa >> 12);
        } else
            pa = (*ppn << 12) | (va & 0xfff);
    }

    return ReadWordPhysAddr(pa);
}

uint64_t MMU::Translate(uint32_t va, Access access) {
    uint64_t ppn = (satp & 0x3fffff) * PAGESIZE;
    int level = LEVELS - 1;
    uint64_t pte_addr;
    uint32_t pte;

    while (1) {
        pte_addr = ppn + (level ? va >> 22 : ((va << 10) >> 22)) * PAGESIZE;
        pte = ReadWordPhysAddr(pte_addr);

        if (!(pte & VBIT))
            throw PageFaultException("Page fault\n", pte);

        if (!(pte & RBIT) && ((pte & WBIT) == WBIT))
            throw PageFaultException("Page fault: WRITE access but not READ", pte);
        
        if (((pte & RBIT) == RBIT) || ((pte & XBIT) == XBIT))
            break;

        if (--level < 0)
            throw PageFaultException("Page fault: level < 0", pte);

        ppn = (uint64_t) (pte >> 10) * PAGESIZE;
    }

    if ((access == READ  && !(pte & RBIT)) ||
        (access == WRITE && !(pte & WBIT)) ||
        (access == EXEC  && !(pte & XBIT)))
        throw PageFaultException("Page fault: access type\n", pte);

    if ((level > 0) && ((pte >> 10) & 0x3ff))
        throw PageFaultException("Page fault: superpage\n", pte);

    if (!(pte & ABIT))
        throw PageFaultException("Page fault: access bit\n", pte);

    if ((access == WRITE) && !(pte & DBIT))
        throw PageFaultException("Page fault: dirty bit\n", pte);

    uint64_t pa = va & 0xfff;

    if (level > 0) {
        pa |= va & 0x3ff000;
        pa |= (uint64_t) (pte & 0xfff00000) << 2;
    } else
        pa |= (uint64_t) (pte & 0xfffffc00) << 2;

    return pa;
}


