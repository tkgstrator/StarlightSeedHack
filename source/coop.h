#pragma once

#include "types.h"
#include <string>
#include <vector> 
#include <utility>

namespace coop
{
class Seedhack
{
public:
    void init(u32);
    void set(u16);
    std::vector<std::string> getGeyser();
    std::string getWaveInfo();
    bool rflag;
    u16 size;
    u32 seed;

    struct Prob
    {
        u16 event[7] = {18, 1, 1, 1, 1, 1, 1};
        u16 tide[3] = {1, 3, 1};
    };

    struct Wave
    {
        u16 event[3] = {0, 0, 0};
        u16 tide[3] = {1, 1, 1};
    };
};
}; // namespace coop