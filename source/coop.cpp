#include "coop.h"
#include "sead/random.h"

namespace coop
{

void Seedhack::init(u32 firstseed)
{
    seed = firstseed;
}

void Seedhack::set(u16 stage)
{
    switch (stage)
    {
    case 3:
        size = 5;
        rflag = true;
        break;
    case 4:
        size = 4;
        rflag = false; // Reuse Random Sead Flag
        break;
    default:
        break;
    }
}

std::string Seedhack::getWaveInfo()
{
    sead::Random rnd;
    rnd.init(seed);

    struct Wave mWave;
    struct Prob mProb;
    std::string waveinfo = "";

    for (u16 wave = 0; wave < 3; ++wave)
    {
        for (u64 event = 0, sum = 0; event < 7; ++event)
        {
            if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))
                continue;
            sum += mProb.event[event];
            if ((rnd.getU32() * sum >> 0x20) < mProb.event[event])
            {
                mWave.event[wave] = event;
            }
        }
        for (u64 tide = 0, sum = 0; tide < 3; ++tide)
        {
            if ((tide == 0) && (1 <= mWave.event[wave] && (mWave.event[wave] <= 3)))
                continue;
            sum += mProb.tide[tide];
            if ((rnd.getU32() * sum >> 0x20) < mProb.tide[tide])
                mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide;
        }
        waveinfo += std::to_string(mWave.tide[wave]) + std::to_string(mWave.event[wave]);
    }
    return waveinfo;
}

std::vector<std::string> Seedhack::getGeyser()
{
    sead::Random rnd;
    std::vector<std::string> gpos(3);
    rnd.init(seed);
    rnd.getU32();

    u32 gameSeed[3] = {seed, rnd.getU32(), rnd.getU32()};

    for (u16 wave = 0; wave < 3; ++wave)
    {
        sead::Random grnd;
        grnd.init(gameSeed[wave]);
        u64 gArray[size];
        // Initialize Array of Geyser
        for (u64 j = 0; j < size; ++j)
        {
            gArray[j] = j;
        }
        for (u16 i = 0; i < 15; ++i)
        {
            for (u64 sel = size - 1; sel > 0; --sel)
            {
                u64 index = (grnd.getU32() * (sel + 1)) >> 0x20;
                std::swap(gArray[sel], gArray[index]);
            }
            gpos[wave] += std::to_string(gArray[0]);
        }
    }
    return gpos;
}
}; // namespace coop