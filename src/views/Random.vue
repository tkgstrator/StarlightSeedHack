<template>
  <v-container fluid>
    <v-form ref="form">
      <v-text-field v-model="mInitialSeed" :rules="rules" label="Initial Seed" required dark dense></v-text-field>
      <v-btn :disabled="!valid" class="mr-2" @click="generate" dark>Generate</v-btn>
    </v-form>
    <v-container class="table">
      <v-data-table :headers="headers" :items="mGameSeed" :items-per-page="100" :mobile-breakpoint="360" dark hide-default-footer dense></v-data-table>
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
    mGameSeed: [],
    headers: [
      {
        text: "Type",
        value: "type",
        align: "center",
        sortable: false,
      },
      {
        text: "Initial Seed",
        value: "mSeed",
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
      this.mGameSeed.splice(0, this.mGameSeed.length)
      let rnd = new Random()
      rnd.init(this.mInitialSeed)
      // rnd.getU32()

      const mGameSeed = [this.mInitialSeed, rnd.getU32(), rnd.getU32(), rnd.getU32(), rnd.getU32(), rnd.getU32(), rnd.getU32()]

      for (let wave = 0; wave < mGameSeed.length; ++wave) {
        rnd.init(mGameSeed[wave])
        for (let loop = 0; loop < 5; ++loop) {
          this.mGameSeed.push({ type: `WAVE${wave + 1}`, mSeed: mGameSeed[wave].toString(16).toUpperCase(), mSeed1: rnd.mSeed1.toString(16).toUpperCase(), mSeed2: rnd.mSeed2.toString(16).toUpperCase(), mSeed3: rnd.mSeed3.toString(16).toUpperCase(), mSeed4: rnd.mSeed4.toString(16).toUpperCase(), mNumber: "-" })
          rnd.getU32()
        }
      }
    }
  }
}

</script>

<style scoped>
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
