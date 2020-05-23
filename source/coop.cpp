#include "coop.h"
#include "sead/random.h"
#include <iostream>

namespace Coop
{
    class Setting {

    };

    class Geyser {

    };

    


    void Seedhack::init(u32 firstseed)
    {
        seed = firstseed;
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

    std::vector<std::string> Seedhack::getGeyser(u16 stage_id)
    {
        sead::Random rnd;
        std::vector<std::string> position(3);
        rnd.init(seed);
        rnd.getU32();

        u32 gameSeed[3] = {seed, rnd.getU32(), rnd.getU32()};
        std::vector<bool> reuse;
        std::vector<std::string> geyser;
        std::vector<std::vector<std::string>> goal;

        for (u16 wave = 0; wave < 3; ++wave)
        {
            sead::Random grnd;
            grnd.init(gameSeed[wave]);
            switch (stage_id)
            {
            case 0:
                reuse = {true, true, true, true, true};
                geyser = {"E", "F", "G", "H", "I"};
                goal = {{"H", "H"}, {"G", "H"}, {"F", "F"}, {"I", "F"}, {"H", "G"}};
                break;
            case 1:
                // size = 4;
                // rflag = false;
                break;
            case 2:
                reuse = {false, true, true, true, true};
                geyser = {"E", "F", "G", "H", "I"};
                goal = {{"H", "H"}, {"G", "H"}, {"I", "F"}, {"I", "F"}, {"G", "H"}};
                break;
            case 3:
                reuse = {true, true, true, true, true};
                geyser = {"C", "D", "E", "F", "G"};
                goal = {{"G", "E"}, {"F", "G"}, {"C", "C"}, {"D", "D"}, {"D", "C"}};
                break;
            case 4:
                reuse = {false, false, false, false};
                geyser = {"D", "E", "F", "G"};
                goal = {{"G"}, {"F"}, {"G"}, {"F"}};
                break;
            default:
                break;
            }
            for (u16 i = 0; i < 15; ++i)
            {
                for (u64 sel = geyser.size() - 1; sel > 0; --sel)
                {
                    u64 index = (grnd.getU32() * (sel + 1)) >> 0x20;
                    std::swap(geyser[sel], geyser[index]);
                    std::swap(reuse[sel], reuse[index]);
                    std::swap(goal[sel], goal[index]);
                }
                // position[wave] += geyser[0];

                if (reuse[0])
                {
                    u64 index = (grnd.getU32() * (goal[0].size())) >> 0x20;
                    // std::string goal = mStage.goal[sel][index];
                    position[wave] += "(" + geyser[0] + goal[0][index] + ")";
                }
                else
                {
                    position[wave] += "(" + geyser[0] + goal[0][0] + ")";
                }
            }
        }
        return position;
    }
}; // namespace coop