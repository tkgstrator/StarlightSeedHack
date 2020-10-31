#include "coop.h"
#include <iostream>

#define N 9
#define LODWORD(x) ((uint32_t)(x & 0xFFFFFFFF))

namespace Coop
{

    bool WaveMgr::isEasyWave(u8 id)
    {
        for (u8 idx = 0; idx < 10; ++idx)
        {
            if (idx <= 7)
                if (id != mAppearIds[idx])
                    return false;
            if (idx >= 8)
                if (id == mAppearIds[idx])
                    return false;
        }
        return true;
    }

    // bool WaveMgr::isEasyWave(u8 id)
    // {
    //     u8 mId = 0;
    //     for (u8 idx = 0; idx < 10; ++idx)
    //     {
    //         if (idx == 0)
    //             mId = mAppearIds[idx]; // 最初の状態をコピーする
    //         if (idx >= 1 && idx <= 7)
    //             if (mId != mAppearIds[idx])
    //                 return false;
    //         if (idx >= 8)
    //             if (mId == mAppearIds[idx])
    //                 return false;
    //     }
    //     return true;
    // }

    u8 WaveMgr::getEnemyAppearId(u64 random, u8 id)
    {
        u8 mArray[3] = {1, 2, 3};
        u8 x9, w9, x10, x11, x12, v17;
        u8 *x7, *w7;
        u64 x8, w8;
        u8 v5 = id; // mAppearId
        u8 x6 = 3;  // mAppearIdMax
        u8 w6 = 3;

        w7 = mArray;
        if (!(v5 & 0x80000000))
        {
            if (!w6)
                return v5;
            w8 = w6 - 1;
            do
            {
                v17 = w8;
                w9 = *w7;
                if (*w7 < v5)
                    break;
                w6 -= w9 == v5;
                if (w9 == v5)
                    break;
                w8 = v17 - 1;
                ++w7;
            } while (v17);
        }
        if (w6 < 1)
            return v5;

        // u8 w6 = id == 3 ? 3 : id + 1; // mAppearIdMax
        x7 = mArray;
        x8 = random * w6 >> 0x20;

        while (1)
        {
            x9 = *x7;
            x10 = x8 == 0 ? 0 : x8 - 1;
            x11 = x8 == 0 ? *x7 : id;
            x12 = x9 == v5 ? 5 : x8 == 0;
            if (x9 != v5)
            {
                x8 = LODWORD(x10);
                id = x11;
            }
            if ((x12 & 7) != 5 && x12 & 7)
                break;
            --x6;
            ++x7;
            if (!x6)
                return v5;
        }
        return id;
    }

    void WaveMgr::getWaveArray()
    {
        sead::Random mRnd; // オオモノ出現のための乱数

        u8 mEnemyAppearId = -1;
        u8 mPhase[35];

        const u8 wave0[35] = {2, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 3, 3, 3, 3}; // 20
        const u8 wave1[35] = {2, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 3, 3}; // 22
        const u8 wave2[35] = {2, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0}; // 24

        if (mWave == 0)
            memcpy(mPhase, wave0, sizeof(u8) * 35);
        if (mWave == 1)
            memcpy(mPhase, wave1, sizeof(u8) * 35);
        if (mWave == 2)
            memcpy(mPhase, wave2, sizeof(u8) * 35);

        u8 mCount = 0;
        for (const u8 &value : mPhase)
        {
            // u8 value = mPhase[idx];

            if (value == 2)
            {
                const u64 random = rnd.getU32();
                mEnemyAppearId = Coop::WaveMgr::getEnemyAppearId(random, mEnemyAppearId);
            }

            if (value == 0)
            {
                const u64 random = rnd.getU32();
                mEnemyAppearId = Coop::WaveMgr::getEnemyAppearId(random, mEnemyAppearId);
                mAppearIds[mCount] = mEnemyAppearId;
                mCount++;
            }

            // オオモノシャケ出現
            if (value == 1)
            {
                mRnd.init(rnd.getU32());
                u16 mRareId = 0;
                for (u64 mProb = 0; mProb < 7; ++mProb)
                {
                    if (!(mRnd.getU32() * (mProb + 1) >> 0x20))
                        mRareId = mProb;
                }
                // printf("RN-> %08X %d\n", random, mRareId);
            }
        }
    }

    // void Ocean::getWaveInfo()
    // {
    //     const u16 mEvent[7] = {18, 1, 1, 1, 1, 1, 1};
    //     const u16 mTide[3] = {1, 3, 1};
    //     rnd.init(mGameSeed);

    //     for (u16 wave = 0; wave < 3; ++wave)
    //     {
    //         for (u64 event = 0, sum = 0; event < 7; ++event) // Calculate Wave Event
    //         {
    //             if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))
    //                 continue;
    //             sum += mEvent[event];
    //             if ((rnd.getU32() * sum >> 0x20) < mEvent[event])
    //                 mWave.event[wave] = event;
    //         }
    //         for (u64 tide = 0, sum = 0; tide < 3; ++tide) // Calculate Wave Tide
    //         {
    //             if ((tide == 0) && (1 <= mWave.event[wave] && (mWave.event[wave] <= 3)))
    //                 continue;
    //             sum += mTide[tide];
    //             if ((rnd.getU32() * sum >> 0x20) < mTide[tide])
    //                 mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide;
    //         }
    //     }
    //     u32 result = mWave.tide[0] * 100000 + mWave.event[0] * 10000 + mWave.tide[1] * 1000 + mWave.event[1] * 100 + mWave.tide[2] * 10 + mWave.event[2];
    //     return result;
    // }

    // bool Ocean::getGeyserValue(u16 stage, u16 wave)
    // {
    //     rnd.init(mGameSeed);
    //     rnd.getU32();
    //     mGeyserSeed[0] = mGameSeed;
    //     mGeyserSeed[1] = rnd.getU32();
    //     mGeyserSeed[2] = rnd.getU32();

    //     switch (stage)
    //     {
    //     case 0:
    //         mReuse = {true, true, true, true, true, true, true, true, true};
    //         mSucc = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
    //         mDist = {999, 999, 999, 999, 167, 300, 188, 465, 316};
    //         break;
    //     case 1:
    //         mReuse = {true, true, true, true, true, true, true, true};
    //         mSucc = {"A", "B", "C", "D", "E", "F", "G", "H"};
    //         mDist = {999, 999, 999, 999, 80, 157, 235, 424};
    //         break;
    //     case 2:
    //         mReuse = {true, true, true, true, true};
    //         mSucc = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
    //         mDist = {999, 999, 999, 999, 258, 329, 199, 366, 225};
    //         break;
    //     case 3:
    //         mReuse = {true, true, true, true, true, true, true};
    //         mSucc = {"A", "B", "C", "D", "E", "F", "G"};
    //         mDist = {999, 999, 405, 348, 165, 131, 151};
    //         break;
    //     case 4:
    //         mReuse = {true, true, true, true, true, true, true};
    //         mSucc = {"A", "B", "C", "D", "E", "F", "G"};
    //         mDist = {999, 999, 999, 999, 0, 999, 999, 999};
    //         break;
    //     default:
    //         break;
    //     }

    //     // switch (stage)
    //     // {
    //     // case 0:
    //     //     mReuse = {true, true, true, true, true};
    //     //     mSucc = {"E", "F", "G", "H", "I"};
    //     //     mDist = {167, 300, 188, 465, 316};
    //     //     break;
    //     // case 1:
    //     //     mReuse = {true, false, true, true};
    //     //     mSucc = {"E", "F", "G", "H"};
    //     //     mDist = {80, 157, 235, 424};
    //     //     break;
    //     // case 2:
    //     //     mReuse = {false, true, true, true, true};
    //     //     mSucc = {"A", "B", "G", "H", "I"};
    //     //     mDist = {258, 329, 199, 366, 225};
    //     //     break;
    //     // case 3:
    //     //     mReuse = {true, true, true, true, true};
    //     //     mSucc = {"C", "D", "E", "F", "G"};
    //     //     mDist = {405, 348, 165, 131, 151};
    //     //     break;
    //     // case 4:
    //     //     mReuse = {false, false, false, false};
    //     //     mSucc = {"D", "E", "F", "G"};
    //     //     mDist = {999, 0, 999, 999};
    //     //     break;
    //     // default:
    //     //     break;
    //     // }

    //     u16 minValue = *std::min_element(mDist.begin(), mDist.end());
    //     sead::Random grnd;
    //     grnd.init(mGeyserSeed[wave]);

    //     std::vector<bool> tReuse;
    //     std::vector<std::string> tSucc;
    //     std::vector<u16> tDist;

    //     std::copy(mSucc.begin(), mSucc.end(), std::back_inserter(tSucc));
    //     std::copy(mReuse.begin(), mReuse.end(), std::back_inserter(tReuse));
    //     std::copy(mDist.begin(), mDist.end(), std::back_inserter(tDist));

    //     for (u16 idx = 0; idx < N; ++idx)
    //     {
    //         for (u64 sel = mSucc.size() - 1; sel > 0; --sel)
    //         {
    //             u64 index = (grnd.getU32() * (sel + 1)) >> 0x20;
    //             std::swap(tSucc[sel], tSucc[index]);
    //             std::swap(tReuse[sel], tReuse[index]);
    //             std::swap(tDist[sel], tDist[index]);
    //         }
    //         if (tReuse[0])
    //             grnd.getU32();

    //         if (tDist[0] != minValue)
    //             return false;
    //     }
    //     return true;
    // }
}; // namespace Coop
