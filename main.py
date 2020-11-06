from library import Ocean

FILENAME = "202020.txt"
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
        with open(FILENAME, mode="r") as f:
            for mLine in f:
                mSeed = int("0x" + mLine, 16)
                mOcean.init(mSeed)
                mOcean.setWaveMgr()  # 常に満潮昼であることはわかっているので無視してよい
                if mSeed >= mProgress * 0x100000:
                    # print("\rmSeed->", hex(m:w
                    # Seed), end="")
                    mProgress += 1
                if isValidWave(mOcean.mWaveMgr):
                    fw.write(mLine)

                counter = [0, 0, 0, 0, 0, 0, 0]
                for idx in range(7):
                    counter[idx] += mOcean.mWaveMgr[2].mBossIds[idx]
                print(mLine.strip(), counter)

                # 途中で処理を終わらせたいときの条件
                if mSeed >= 0x100:
                    break
