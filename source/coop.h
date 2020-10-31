#pragma once

#include "types.h"
#include "sead/random.h"
#include <regex>
#include <omp.h>
#include <string>
#include <vector>
#include <utility>
#include <new>

namespace Coop
{
    class WaveMgr
    {
    public:
        WaveMgr() : mWaveSeed(0) {}
        WaveMgr(u8 wave, u32 seed) : mWaveSeed(seed), mWave(wave)
        {
            rnd.init(mWaveSeed);
            rnd.getU32();
            getWaveArray();
        }
        ~WaveMgr() = default;

        // メンバ変数
        sead::Random rnd; // WAVEごとの乱数生成器
        u32 mWaveSeed;
        u16 mWave;
        void getWaveArray();
        u8 getEnemyAppearId(u64, u8);
        bool isEasyWave(u8);

    protected:
        u8 mAppearIds[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    };

    class Ocean
    {
    public:
        Ocean(u32 seed) : mGameSeed(seed)
        {
            rnd.init(mGameSeed);
            rnd.getU32();
            mWaveMgr[0] = WaveMgr(0, mGameSeed);
            mWaveMgr[1] = WaveMgr(1, rnd.getU32());
            mWaveMgr[2] = WaveMgr(2, rnd.getU32());
        }
        ~Ocean() = default;

        // void getWaveInfo();
        u8 mWave[3]; // 三つのWAVEの情報が入っている
        WaveMgr mWaveMgr[3];

    private:
        sead::Random rnd;    // ゲーム乱数生成器
        const u32 mGameSeed; // ゲームシード
    };
}; // namespace Coop