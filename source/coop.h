#pragma once

#include "types.h"
#include <string> 

namespace coop
{
class Seedhack
{
public:
    u32 getWaveInfo(u32, u32);
    void getGeyser(u32, u32);

    std::string gpos[3];
    struct Prob
    {
        int event[7] = {18, 1, 1, 1, 1, 1, 1};
        int tide[3] = {1, 3, 1};
    };

    struct Wave
    {
        int event[3] = {0, 0, 0};
        int tide[3] = {1, 1, 1};
    };
};
}; // namespace coop