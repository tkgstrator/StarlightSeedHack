from library import Ocean

FILENAME = "222122.txt"
OUTPUT = "Output.txt"

# FILENAME = "Output.txt"
# OUTPUT = "Output[1].txt"


def isValidWave(mWaveMgr):

    for wave in range(3):  # WAVE3までをループ
        mSum = [0, 0, 0, 0, 0, 0, 0]  # オオモノの湧き数を保存
        for index, line in enumerate(mWaveMgr[wave].mBossAppearIds):
            mAppearId = line[0]  # 0番目の要素は湧き方向
            mBoss = line[1]  # 1番目の要素は湧いたオオモノ配列
    return True  # NG条件を見たなさなければTrueを返す


if __name__ == "__main__":
    with open(OUTPUT, mode="w") as fw:
        mProgress = 0x0
        mOcean = Ocean.Ocean()

        # for mSeed in range(0xFFFFFFFF):
        #     mOcean.init(mSeed)
        #     mOcean.getWaveInfo()
            
        #     if mOcean.mEvent[1] == 1 and mOcean.mTide[1] == 1:
        #         mOcean.setWaveMgr()  # 常に満潮昼であることはわかっているので無視してよい
        #         # print("\r", mSeed)
        #         if mOcean.mWaveMgr[1].mAppearIds[0] == 1:
        #             print(mSeed, mOcean.mWaveMgr[1].mAppearIds[0])

        with open(FILENAME, mode="r") as f:
            for mLine in f:
                mSeed = int("0x" + mLine, 16)
                mOcean.init(mSeed)
                mOcean.getWaveInfo()
                
                # if mSeed >= mProgress * 0x100000:
                #     # print("\rmSeed->", hex(m:w
                #     # Seed), end="")
                #     mProgress += 1
                # if isValidWave(mOcean.mWaveMgr):
                #     fw.write(mLine)
                mOcean.setWaveMgr()
                print("Geyser", mOcean.mWaveMgr[0].getGeyserPos())
                print(hex(mOcean.mGameSeed), mOcean.mEvent, mOcean.mTide)
                break
                # counter = [0, 0, 0, 0, 0, 0, 0]
                # for idx in range(7):
                #     counter[idx] += mOcean.mWaveMgr[2].mBossIds[idx]
                # print(mLine.strip(), counter)

                # 途中で処理を終わらせたいときの条件
                # if mSeed >= 0x100:
                #     break
