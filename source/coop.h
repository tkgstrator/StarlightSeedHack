#pragma once

#include "types.h"
#include <string> 

namespace coop
{
class Seedhack
{
public:
    void init(u32);
    u32 getWaveInfo();
    void getGeyser(u32);

    std::string gpos[3];
    u32 seed;

    struct Prob
    {
        u32 event[7] = {18, 1, 1, 1, 1, 1, 1};
        u32 tide[3] = {1, 3, 1};
    };

    struct Wave
    {
        u32 event[3] = {0, 0, 0};
        u32 tide[3] = {1, 1, 1};
    };
};
}; // namespace coop