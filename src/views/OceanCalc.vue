<template>
  <v-container fluid>
    <v-form ref="form">
      <v-text-field v-model="mInitialSeed" :rules="rules" label="Initial Seed" required dark dense></v-text-field>
      <v-btn :disabled="!valid" class="mr-2" @click="generate" dark>Generate</v-btn>
    </v-form>
    <v-container class="table">
      <v-data-table :headers="headers" :items="mOceanInfo" :items-per-page="100" :mobile-breakpoint="360" dark hide-default-footer dense></v-data-table>
    </v-container>
  </v-container>
</template>

<script>
class Wave {
  constructor() {
    this.event = [0, 0, 0]
    this.tide = [1, 1, 1]
  }
}

class Prob {
  constructor() {
    this.event = [18, 1, 1, 1, 1, 1, 1];
    this.tide = [1, 3, 1]
  }
}

class Ocean {
  constructor() { }

  init(seed) {
    this.rnd = new Random()
    this.rnd.init(seed)
    this.rnd.getU32()
  }

  getId(flg) {
    let mRareId = "-"

    const mRareType = ["Steelhead", "Flyfish", "Scrapper", "Steel Eel", "Tower", "Maws", "Drizzler"] // オオモノテーブルだけどこれで合っているのかは謎
    let rnd = new Random()
    rnd.init(this.rnd.getU32())

    if (flg != 1)
      return mRareId

    for (let mProb = 0, mTmpId = ""; mProb < mRareType.length; ++mProb) {
      if (mRareType.length <= mProb)
        mTmpId = mRareType[0]
      else
        mTmpId = mRareType[mProb]
      if (!(parseInt((rnd.getU32() * (mProb + 1)) / Math.pow(2, 0x20))))
        mRareId = mTmpId
    }
    return mRareId
  }
}

class Random {
  constructor() { }

  init(seed) {
    this.mSeed1 = (Math.imul(0x6C078965, (seed ^ (seed >>> 30))) + 1) >>> 0;
    this.mSeed2 = (Math.imul(0x6C078965, (this.mSeed1 ^ (this.mSeed1 >>> 30))) + 2) >>> 0;
    this.mSeed3 = (Math.imul(0x6C078965, (this.mSeed2 ^ (this.mSeed2 >>> 30))) + 3) >>> 0;
    this.mSeed4 = (Math.imul(0x6C078965, (this.mSeed3 ^ (this.mSeed3 >>> 30))) + 4) >>> 0;
  }

  getU32() {
    let n = (this.mSeed1 ^ (this.mSeed1 << 11)) >>> 0;
    this.mSeed1 = this.mSeed2;
    this.mSeed2 = this.mSeed3;
    this.mSeed3 = this.mSeed4;
    this.mSeed4 = ((n ^ (n >>> 8) ^ this.mSeed4 ^ (this.mSeed4 >>> 19))) >>> 0;

    return this.mSeed4;
  }
}

export default {
  data: () => ({
    valid: true,
    rules: [
      v => (parseInt(v) <= 0xFFFFFFFF && 0x0 <= parseInt(v)) || "Initial Seed must be number"
    ],
    mInitialSeed: 0x0,
    mOceanInfo: [],
    headers: [
      {
        text: "Description",
        value: "type",
        align: "center",
        sortable: false,
      },
      {
        text: "WAVE1",
        value: "mWave1",
        align: "center",
        sortable: false,
      },
      {
        text: "WAVE2",
        value: "mWave2",
        align: "center",
        sortable: false,
      },
      {
        text: "WAVE3",
        value: "mWave3",
        align: "center",
        sortable: false,
      },
    ]
  }),

  methods: {
    generate() {
      // まずは全要素を空っぽにする
      this.mOceanInfo.splice(0, this.mOceanInfo.length)

      let mGameSeed = [this.mInitialSeed] // 各WAVEの乱数生成器を初期化するシード

      let grnd = new Random() // ゲーム乱数生成器
      grnd.init(this.mInitialSeed) // 初期シードでゲーム乱数生成器を初期化

      // 潮位とイベントを先読み
      let mWave = new Wave() // WAVE情報を保存するクラス
      const mProb = new Prob() // 確率情報をもっているクラス（配列でよくね？）

      for (let wave = 0; wave < 3; ++wave) {
        for (let event = 0, sum = 0; event < 7; ++event) {
          if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))
            continue;
          sum += mProb.event[event]
          if ((grnd.getU32() * sum / Math.pow(2, 32)) < mProb.event[event])
            mWave.event[wave] = event
        }
        for (let tide = 0, sum = 0; tide < 3; ++tide) {
          if ((tide == 0) && (1 <= mWave.event[wave] && (mWave.event[wave] <= 3)))
            continue;
          sum += mProb.tide[tide];
          if ((grnd.getU32() * sum / Math.pow(2, 32)) < mProb.tide[tide])
            mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide
        }
      }
      this.mOceanInfo.push({ type: "Tide", mWave1: tide(mWave.tide[0]), mWave2: tide(mWave.tide[1]), mWave3: tide(mWave.tide[2]) })
      this.mOceanInfo.push({ type: "Event", mWave1: event(mWave.event[0]), mWave2: event(mWave.event[1]), mWave3: event(mWave.event[2]) })


      grnd.init(this.mInitialSeed) // 初期シードでゲーム乱数生成器を初期化
      grnd.getU32() // 謎の一発乱数消費
      mGameSeed.push(grnd.getU32())
      mGameSeed.push(grnd.getU32())

      // パラメータ
      const mWaveArray = [
        [-1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, -1, -1, -1, -1], // 20
        [-1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, -1, -1, 0, 0], // 22
        [-1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0], // 24
      ]

      // 全WAVEを計算する
      let ocean = [new Ocean(), new Ocean(), new Ocean()]
      ocean[0].init(mGameSeed[0])
      ocean[1].init(mGameSeed[1])
      ocean[2].init(mGameSeed[2])

      for (let loop = 0; loop < 35; ++loop) {
        let mRareArray = []
        for (let wave = 0; wave < 3; ++wave) {
          if (mWave.event[wave] == 0)
            mRareArray.push(ocean[wave].getId(mWaveArray[wave][loop]))
          else
            mRareArray.push("-")
        }
        // if (mWaveArray[wave][loop] == 1)
        this.mOceanInfo.push({ type: `${loop + 1}`, mWave1: mRareArray[0], mWave2: mRareArray[1], mWave3: mRareArray[2] })
      }
    }
  }
}

// function dechex(number) {
//   return ("00000000" + number.toString(16).toUpperCase()).slice(-8)
// }

function tide(number) {
  switch (number) {
    case 0:
      return "Low"
    case 1:
      return "Normal"
    case 2:
      return "High"
  }
}

function event(number) {
  switch (number) {
    case 0:
      return "No Event"
    case 1:
      return "Rush"
    case 2:
      return "Goldie Seeking"
    case 3:
      return "Griller"
    case 4:
      return "The Mothership"
    case 5:
      return "Fog"
    case 6:
      return "Cohock Charge"
    default:
      return
  }
}
</script>

<style>
@import url("https://fonts.googleapis.com/css2?family=Roboto+Mono:wght@300&display=swap");

.container {
  max-width: 800px;
  font-family: "Splatfont";
  color: #eeeeee;
  padding: 5px !important;
}

body {
  /* margin: 0 auto; */
  background-color: #111111;
  /* width: 99%; */
}
</style>
<style scoped>
h1 {
  font-family: "Splatfont";
  color: #eeeeee;
}

p {
  font-family: "Splatfont";
  color: #eeeeee;
}

.v-list-item__title {
  font-family: "Splatfont";
}

.wave {
  width: 33%;
}

.table {
  font-family: "Splatfont2";
  /* font-family: "Roboto Mono", monospace; */
}

button {
  background-color: #222222 !important;
  border: 2px solid;
  border-color: #eeeeee;
  border-radius: 3px;
  box-shadow: none;
}
/* .v-application .success {
  all: unset;
  background-color: #111111 !important;
} */
.v-data-table {
  white-space: pre-line;
}

td {
  font-size: 18px !important;
}

table.v-table thead th {
  font-size: 20px !important;
}

.v-input {
  display: block;
  margin: 0 auto;
  min-width: 400px;
  width: 50%;
  max-width: 600px;
}
</style>
