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
    std::vector<std::string> getGeyser(u32);
    std::string getWaveInfo();
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