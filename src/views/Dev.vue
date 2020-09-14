<template>
  <v-container fluid>
    <v-form ref="form">
      <v-text-field v-model="mInitialSeed" :rules="rules" label="Initial Seed" required dark dense></v-text-field>
      <v-btn :disabled="!valid" class="mr-2" @click="generate" dark>Generate</v-btn>
    </v-form>
    <v-container class="table">
      <v-data-table :headers="headers" :items="mRareArray" :items-per-page="100" :mobile-breakpoint="360" dark hide-default-footer dense></v-data-table>
    </v-container>
  </v-container>
</template>

<script>
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
    mRareArray: [],
    headers: [
      {
        text: "Description",
        value: "type",
        align: "center",
        sortable: false,
      },
      {
        text: "mSeed1",
        value: "mSeed1",
        align: "center",
        sortable: false,
      },
      {
        text: "mSeed2",
        value: "mSeed2",
        align: "center",
        sortable: false,
      },
      {
        text: "mSeed3",
        value: "mSeed3",
        align: "center",
        sortable: false,
      },
      {
        text: "mSeed4",
        value: "mSeed4",
        align: "center",
        sortable: false,
      },
      {
        text: "getU32()",
        value: "mNumber",
        align: "center",
        sortable: false,
      },
    ]
  }),

  methods: {
    generate() {
      // まずは全要素を空っぽにする
      this.mRareArray.splice(0, this.mRareArray.length)

      let mGameSeed = [this.mInitialSeed] // 各WAVEの乱数生成器を初期化するシード
      let grnd = new Random() // ゲーム乱数生成器
      grnd.init(this.mInitialSeed) // 初期シードでゲーム乱数生成器を初期化
      grnd.getU32()
      mGameSeed.push(grnd.getU32())
      mGameSeed.push(grnd.getU32())
      // パラメータ
      const mRareType = ["Steelhead", "Flyfish", "Scrapper", "Steel Eel", "Tower", "Maws", "Drizzler"] // オオモノテーブルだけどこれで合っているのかは謎
      const mWave = [
        [-1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0], // 20
        [-1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0], // 22
        [-1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0], // 24
      ]

      console.log(dechex(mGameSeed[0]), dechex(mGameSeed[1]), dechex(mGameSeed[2]))

      // 全WAVEを計算する
      for (let wave = 0; wave < 3; ++wave) {
        let rnd = new Random()
        rnd.init(mGameSeed[wave])
        rnd.getU32() // Initialize
        for (let loop = 0; loop < mWave[wave].length; ++loop) {
          const srnd = new Random()
          srnd.init(rnd.getU32()) // Initialize with seed genarated by rnd

          // if (!mWave[wave][loop])
          //   continue;

          let mWeight = 0
          let mProb = 0
          let mTmpId = ""
          let mRareId = ""

          do {
            if (mRareType.length <= mProb)
              mTmpId = mRareType[0]
            else
              mTmpId = mRareType[mProb]

            ++mWeight
            if (!(parseInt((srnd.getU32() * mWeight) / Math.pow(2, 0x20))))
              mRareId = mTmpId
            if (mProb <= 6)
              ++mProb
            else
              mProb = 6
            // console.log(mProb, mWeight, mRareId, mTmpId)
          } while (mProb != mRareType.length)
          let mSeeds = [rnd.mSeed1, rnd.mSeed2, rnd.mSeed3, rnd.mSeed4]
          // if (mWave[wave][loop] == 0)
          //   this.mRareArray.push({ type: `Wave${wave + 1}(${loop + 1})`, mSeed1: dechex(mSeeds[0]), mSeed2: dechex(mSeeds[1]), mSeed3: dechex(mSeeds[2]), mSeed4: dechex(mSeeds[3]), mNumber: "-" })
          // if (mWave[wave][loop] == 1)
          this.mRareArray.push({ type: `Wave${wave + 1}(${loop + 1})`, mSeed1: dechex(mSeeds[0]), mSeed2: dechex(mSeeds[1]), mSeed3: dechex(mSeeds[2]), mSeed4: dechex(mSeeds[3]), mNumber: mRareId })
        }
      }
    }
  }
}

function dechex(number) {
  return ("00000000" + number.toString(16).toUpperCase()).slice(-8)
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
