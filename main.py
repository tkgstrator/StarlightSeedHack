from library import Ocean

FILENAME = "202020.txt"
if __name__ == "__main__":
    with open(FILENAME, mode="r") as f:
        for mSeed in f:
            mOcean = Ocean.Ocean(int(mSeed))
            mOcean.setWaveMgr() # 常に満潮昼であることはわかっているので無視してよい
            print(mOcean.mEvent, mOcean.mTide)
            print(mOcean.mWaveMgr[0].mBossAppearIds)
            print(mOcean.mWaveMgr[1].mBossAppearIds)
            print(mOcean.mWaveMgr[2].mBossAppearIds)
            break
        # print(mOcean.mWaveMgr[0].mAppearIds, mOcean.mWaveMgr[0].mBossIds)
        # print(mOcean.mWaveMgr[1].mAppearIds, mOcean.mWaveMgr[1].mBossIds)
        # print(mOcean.mWaveMgr[2].mAppearIds, mOcean.mWaveMgr[2].mBossIds)