#pragma once
#include <map>
#include <queue>

template<typename value_t>
class Cache
{
public:
    static constexpr uint32_t size = 512;
private:
    std::map<uint32_t, value_t> mem;
    std::queue<uint32_t> keys;
    size_t hits;
    size_t misses;
public:
    bool in_cache (const uint32_t& key) {
        return mem.find(key) != mem.end();
    }

    uint64_t GetMisses () {
        return misses;
    }

    uint64_t GetHits () {
        return hits;
    }

    void put (const uint32_t& key, const value_t& value) {
        if (!in_cache(key))
        {
            if (mem.size() == size) {
                mem.erase(keys.front());
                keys.pop();
                keys.push(key);
            }
            mem[key] = value;
        }
    }

    value_t* get (const uint32_t& key) {
        if (in_cache(key)) {
            hits++;
            return &mem[key];
        }
        else {
            misses++;
            return NULL;
        }
    }
};

