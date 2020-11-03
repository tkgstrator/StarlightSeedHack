from library import Ocean

if __name__ == "__main__":
    mOcean = Ocean.Ocean(1)
    print(mOcean.mEvent, mOcean.mTide)
    mOcean.setWaveMgr()
    print(mOcean.mWaveMgr[0].mAppearIds, mOcean.mWaveMgr[0].mBossIds)
    print(mOcean.mWaveMgr[1].mAppearIds, mOcean.mWaveMgr[1].mBossIds)
    print(mOcean.mWaveMgr[2].mAppearIds, mOcean.mWaveMgr[2].mBossIds)