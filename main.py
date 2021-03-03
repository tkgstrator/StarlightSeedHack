from library import Ocean
from enum import Enum
from graphviz import Digraph
import collections

FILENAME = "Outputs.txt"
OUTPUT = "Output.txt"

class Boss(Enum):
    STEELHEAD = 0
    FLYFISH = 1
    SCRAPPER = 2
    STEELEEL = 3
    TOWER = 4
    MAWS = 5
    DRIZZLER = 6


def isValidWave(mWaveMgr):

    for wave in range(3):  # WAVE3までをループ
        mIds = mWaveMgr[wave].mBossAppearIds
        if wave != 2:
            continue

        mCount = 0x0
        for index, line in enumerate(mIds):
            mAppearId = line[0]  # 0番目の要素は湧き方向
            mBoss = line[1]  # 1番目の要素は湧いたオオモノ配列

            if index == 6:
                if mAppearId != 3:
                    return False

            if index == 7:
                if 5 not in mBoss:
                    return False

            # 三回の湧き変化で詰まる
            if index <= 6:
                mTmp = mIds[index][1] + mIds[index + 1][1]
                if mTmp.count(5) >= 4: # モグラ
                    return False

            if index <= 5:
                mTmp = mIds[index][1] + mIds[index + 1][1] + mIds[index + 2][1]
                for idx in [2, 3, 6]: # テッパンとヘビとコウモリ
                    if mTmp.count(idx) >= 4:
                        return False
            if index <= 4:
                mTmp = mIds[index][1] + mIds[index + 1][1] + mIds[index + 2][1] + mIds[index + 3][1]
                if mTmp.count(0) >= 4: # バクダン
                    return False
            if index >= 3:
                if 6 in mBoss:
                    return False
    return True  # NG条件を見たなさなければTrueを返す


if __name__ == "__main__":

    Graph = Digraph(format="png")
    Graph.attr("node", shape="circle")
    # Graph.attr("node", shape="circle", label="")

    with open(OUTPUT, mode="w") as fw:
        mProgress = 0x0
        mCount = 0x1
        mOcean = Ocean.Ocean()
        
        with open(FILENAME, mode="r") as f:
            edges = []
            for index, mLine in enumerate(f):
                mSeed = int("0x" + mLine, 16)
                mOcean.init(mSeed)
                mOcean.setWaveMgr()  # 常に満潮昼であることはわかっているので無視してよい

                node = mOcean.mWaveMgr[0].getGeyserPos(3) # ノードを取得
                for idx, _ in enumerate(node):
                    if idx == 0:
                        edges.append((None, node[idx]))
                    if idx >= 1:
                        edges.append((node[idx - 1], node[idx]))

                if mSeed >= mProgress * 0x10000:
                    print(f"\rmIndex-> {hex(index)} mSeed->{hex(mSeed)}", end="")
                    mProgress += 1
                if index > 0x10000:
                    break
                
                # if mSeed >= mProgress * 0x100000:
                #     print("\rmSeed->", hex(mSeed), mCount/(index+1), end="")
                #     mProgress += 1
                # if isValidWave(mOcean.mWaveMgr):
                #     mCount += 1
                #     fw.write(mLine)
    # まずはノードを作成する

    nodes = collections.Counter(edges)
    for (parent, child), count in nodes.items():
        if parent == None:
            Graph.node(str(parent), "")
        else:
            Graph.node(str(parent), parent[-1])
            Graph.node(str(child), child[-1])
        Graph.edge(str(parent), str(child), label=f"{str(count)}")
    Graph.render("GoldieSeeking")