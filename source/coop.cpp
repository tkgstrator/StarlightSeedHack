#include "coop.h"
#include "sead/random.h"
#include <utility>

namespace coop
{

void Seedhack::init(u32 firstseed)
{
    seed = firstseed;
}

u32 Seedhack::getWaveInfo()
{
    sead::Random rnd;
    rnd.init(seed);

    struct Wave mWave;
    struct Prob mProb;
    u64 sum = 0;
    u32 info = 0;

    for (u32 wave = 0; wave < 3; wave++)
    {
        for (u32 event = 0; event < 7; event++)
        {
            if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))
                continue;
            sum += mProb.event[event];
            if ((rnd.getU32() * sum >> 0x20) < mProb.event[event])
            {
                mWave.event[wave] = event;
            }
        }
        // if (mWevent[wave] != )
        sum = 0; // Re initialize
        for (u32 tide = 0; tide < 3; tide++)
        {
            if ((tide == 0) && (1 <= mWave.event[wave] && (mWave.event[wave] <= 3)))
                continue;
            sum += mProb.tide[tide];
            if ((rnd.getU32() * sum >> 0x20) < mProb.tide[tide])
                mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide;
        }
        info = info * 100 + mWave.tide[wave] * 10 + mWave.event[wave];
    }
    return info;
}

void Seedhack::getGeyser(u32 size)
{
    sead::Random rnd;
    rnd.init(seed);

    rnd.getU32();
    
    u32 gameSeed[3] = {seed, rnd.getU32(), rnd.getU32()};

    for (u32 wave = 0; wave < 3; wave++)
    {
        sead::Random grnd;
        grnd.init(gameSeed[wave]);
        u64 gArray[size];
        // Initialize Array of Geyser
        gpos[wave] = "";
        for (u64 j = 0; j < size; j++)
        {
            gArray[j] = j;
        }
        for (u64 i = 0; i < 12; i++)
        {
            for (u64 sel = size - 1; sel > 0; sel--)
            {
                u64 index = (grnd.getU32() * (sel + 1)) >> 0x20;
                std::swap(gArray[sel], gArray[index]);
            }
            gpos[wave] += std::to_string(gArray[0]);
        }
    }
}
}; // namespace coop