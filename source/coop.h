#pragma once

#include "types.h"
#include "sead/random.h"
#include <regex>
#include <omp.h>
#include <string>
#include <vector>
#include <utility>

namespace Coop
{
    class Setting
    {
    public:
        Setting(u32 seed, bool fast = true, bool regex = false) : mSeed{seed}, mFast{fast}, mRegex{regex}
        {
            rnd.init(seed);
        };
        Setting();
        ~Setting() = default;
        void getWaveInfo(std::string);
        std::string mSetting;
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

    protected:
        sead::Random rnd;
        u32 mSeed;
        bool mFast;
        bool mRegex;
    };

    class Geyser
    {
    public:
        Geyser(u16 stage, u32 seed);
        ~Geyser() = default;
        void getGeyser();
        std::vector<std::string> mPosition = {"", "", ""};

    private:
        sead::Random rnd;
        sead::Random grnd;
        std::vector<u32> mGameSeed;
        std::vector<bool> mReuse;
        std::vector<std::string> mSucc;
        std::vector<std::vector<std::string>> mGoal;
    };
}; // namespace Coop