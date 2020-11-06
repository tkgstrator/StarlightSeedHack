from library import NSRandom


class Ocean:
    def __init__(self):
        self.rnd = NSRandom.NSRandom()  # シードごとの乱数生成器（ボス的な存在
        self.mEvent = [0, 0, 0]  # イベント情報
        self.mTide = [0, 0, 0]  # 潮位情報
        self.mWaveMgr = []  # 各WAVE情報は最初はNoneを保持
        self.mGameSeed = 0x00000000  # 設定された初期ゲームシード

    def init(self, seed):
        self.mGameSeed = seed  # GAME SEEDをセット
        self.getWaveInfo()

    def setWaveMgr(self):  # 各WAVEの情報を計算する 無条件に初期化するとこれ結構重いので時間かかる
        self.rnd.init(self.mGameSeed)  # WAVE情報を求めるために初期化
        self.rnd.getU32()  # 乱数を一回消費
        self.mWaveMgr = [
            WaveMgr(0, self.mGameSeed),
            WaveMgr(1, self.rnd.getU32()),
            WaveMgr(2, self.rnd.getU32()),
        ]

    def getWaveInfo(self):  # WAVEの情報を計算する
        mEventProb = [18, 1, 1, 1, 1, 1, 1]
        mTideProb = [1, 3, 1]
        self.rnd.init(self.mGameSeed)  # WAVE情報を求めるために初期化

        for wave in range(3):
            sum = 0
            for event in range(7):
                if (
                    (wave > 0)
                    and (self.mEvent[wave - 1] != 0)
                    and (self.mEvent[wave - 1] == event)
                ):
                    continue
                sum += mEventProb[event]
                if (self.rnd.getU32() * sum >> 0x20) < mEventProb[event]:
                    self.mEvent[wave] = event
            sum = 0
            for tide in range(3):
                if tide == 0 and 1 <= self.mEvent[wave] and self.mEvent[wave] <= 3:
                    continue
                sum += mTideProb[tide]
                if (self.rnd.getU32() * sum >> 0x20) < mTideProb[tide]:
                    self.mTide[wave] = 0 if self.mEvent[wave] == 6 else tide


class WaveMgr:
    rnd = NSRandom.NSRandom()  # WAVE用の乱数生成器
    mWaveNum = 0x0  # WAVE数
    mWaveSeed = 0x00000000  # WAVE SEED
    mWaveArray = [
        # 0は湧き方向変化, 1はオオモノ出現, 2は乱数消費のみ, 3は揃えるためにあって何もしない
        [
            2,
            0,
            1,
            1,
            0,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            0,
            0,
            3,
            3,
            3,
            3,
        ],  # 20
        [
            2,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            0,
            0,
            3,
            3,
        ],  # 22
        [
            2,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
            0,
            1,
            1,
            1,
            1,
            0,
            1,
            0,
            0,
        ],  # 24
    ]
    mEnemyAppearId = -1  # 湧き方向を-1で初期化

    def __init__(self, wave, seed):
        self.mWaveSeed = seed  # WAVE SEEDをセット
        self.mWaveNum = wave  # WAVE数をセット
        self.mAppearIds = []  # 湧き方向配列
        self.mBossIds = []  # 出現するオオモノの配列
        self.mBossAppearIds = []  ## 出現するオオモノと湧き方向をまとめたもの
        self.rnd.init(self.mWaveSeed)
        self.rnd.getU32()
        self.getWaveArray()

    def getWaveArray(self):  # 湧き方向とオオモノの種類を出力
        mArray = self.mWaveArray[self.mWaveNum]  # WAVE配列をセット
        mTmp = []  # 仮の配列
        for index, value in enumerate(mArray):
            if value == 2:  # 初期化のみ
                random = self.rnd.getU32()
                self.mEnemyAppearId = self.getEnemyAppearId(random, self.mEnemyAppearId)
            if value == 0:  # 湧き方向が変化した
                if index != 1:
                    self.mBossAppearIds.append([self.mEnemyAppearId, mTmp])
                    mTmp = []
                random = self.rnd.getU32()
                self.mEnemyAppearId = self.getEnemyAppearId(random, self.mEnemyAppearId)
                self.mAppearIds.append(self.mEnemyAppearId)
            if value == 1:  # オオモノが出現した
                mRnd = NSRandom.NSRandom()
                mRnd.init(self.rnd.getU32())

                mRareId = 0
                for mProb in range(7):
                    if not (mRnd.getU32() * (mProb + 1) >> 0x20):
                        mRareId = mProb
                self.mBossIds.append(mRareId)
                mTmp.append(mRareId)

    def getEnemyAppearId(self, random, id):  # 湧き方向を計算する関数
        mArray = [1, 2, 3]
        mIndex = 0  # ポインタっぽい役割をするためのインデックス
        w6 = 3
        x6 = 3
        v5 = id
        w7 = mArray
        if not (id & 0x80000000):
            w8 = w6 - 1
            while True:
                v17 = w8
                w9 = w7[mIndex]
                if w9 < id:
                    break
                w6 -= w9 == id
                if w9 == id:
                    break
                w8 = v17 - 1
                mIndex += 1
                if not v17:
                    break

        mIndex = 0
        x7 = mArray
        x8 = 0xFFFFFFFF & (random * w6 >> 0x20)  # 乱数を消費して湧き方向を計算

        while True:
            x9 = x7[mIndex]
            x10 = 0 if x8 == 0 else x8 - 1
            x11 = x9 if x8 == 0 else v5
            x12 = 5 if x9 == v5 else x8 == 0
            if x9 != v5:
                x8 = 0xFFFFFFFF & x10
                id = x11
            if (x12 & 7) != 5 and (x12 & 7):
                break
            x6 -= 1
            mIndex += 1
            if not x6:
                return v5
        return id
