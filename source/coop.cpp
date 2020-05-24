#include "coop.h"
#include <iostream>

namespace Coop
{
    bool Setting::getWaveInfo(std::string mWaveInfo)
    {
        struct Wave mWave;
        struct Prob mProb;
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
            std::string tmp = std::to_string(mWave.tide[wave]) + std::to_string(mWave.event[wave]);
            if (mRegex) // mRegex is Enable
                if (!std::regex_match(mSetting, std::regex(mWaveInfo.substr(wave * 2, 2))))
                    return false;
            // if (mFast) // mFast is Enable
            // {
            //     // std::cout << "Seed: " << mSeed << " Comp: " << tmp << "=>" <<mWaveInfo.substr(wave * 2, 2) << std::endl;
            //     if (mRegex) // mRegex is Enable
            //         if (!std::regex_match(mSetting + tmp, std::regex(mWaveInfo.substr(0, wave * 2 + 2))))
            //             throw - 1;
            //     if (!mRegex) // mRegex is Disable
            //         if (mWaveInfo.substr(wave * 2, 2) != tmp)
            //             throw - 1;
            // }
            mSetting += tmp;
        }
        return true;
    }

    Geyser::Geyser(u16 stage, u32 seed)
    {
        rnd.init(seed);
        rnd.getU32();
        mGameSeed = {seed, rnd.getU32(), rnd.getU32()};

        switch (stage)
        {
        case 0:
            mReuse = {true, true, true, true, true};
            mSucc = {"E", "F", "G", "H", "I"};
            mGoal = {{"H", "H"}, {"G", "H"}, {"F", "F"}, {"I", "F"}, {"H", "G"}};
            break;
        case 1:
            // size = 4;
            // rflag = false;
            break;
        case 2:
            mReuse = {false, true, true, true, true};
            mSucc = {"E", "F", "G", "H", "I"};
            mGoal = {{"H", "H"}, {"G", "H"}, {"I", "F"}, {"I", "F"}, {"G", "H"}};
            break;
        case 3:
            mReuse = {true, true, true, true, true};
            mSucc = {"C", "D", "E", "F", "G"};
            mGoal = {{"G", "E"}, {"F", "G"}, {"C", "C"}, {"D", "D"}, {"D", "C"}};
            break;
        case 4:
            mReuse = {false, false, false, false};
            mSucc = {"D", "E", "F", "G"};
            mGoal = {{"G"}, {"F"}, {"G"}, {"F"}};
            break;
        default:
            break;
        }
    }

    void Geyser::getGeyser()
    {
        for (u16 wave = 0; wave < 3; ++wave)
        {
            // ??????
            std::vector<bool> tReuse;
            std::vector<std::string> tSucc;
            std::vector<std::vector<std::string>> tGoal;
            std::copy(mSucc.begin(), mSucc.end(), std::back_inserter(tSucc));
            std::copy(mReuse.begin(), mReuse.end(), std::back_inserter(tReuse));
            std::copy(mGoal.begin(), mGoal.end(), std::back_inserter(tGoal));

            grnd.init(mGameSeed[wave]);
            for (u16 i = 0; i < 15; ++i)
            {
                for (u64 sel = tSucc.size() - 1; sel > 0; --sel)
                {
                    u64 index = (grnd.getU32() * (sel + 1)) >> 0x20;
                    std::swap(tSucc[sel], tSucc[index]);
                    std::swap(tReuse[sel], tReuse[index]);
                    std::swap(tGoal[sel], tGoal[index]);
                }
                mPosition[wave] += tSucc[0];
                // mPosition[wave] += "(" + mSucc[0] + mGoal[0][!mReuse[0] ? 0 : (grnd.getU32() * (mGoal[0].size())) >> 0x20] + ")";
                // mPosition[wave] += "(" + mSucc[0] + mGoal[0][!mReuse[0] ? 0 : (grnd.getU32() * (mGoal[0].size())) >> 0x20] + ")";
            }
        }
    }
}; // namespace Coop