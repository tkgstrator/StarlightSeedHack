<template>
  <v-container fluid>
    <v-form v-model="valid" lazy-validation ref="form">
      <!-- <v-col class="d-flex" cols="6" sm="12"> -->
      <!-- <v-select :items="version" label="Version" dense dark></v-select> -->
      <!-- <v-select :items="version" label="Options" dense dark></v-select> -->
      <!-- </v-col> -->
      <v-col class="d-flex">
        <v-select :items="event" item-text="title" label="Wave1" dense dark class="wave" v-model="wave1"></v-select>
        <v-select :items="event" item-text="title" label="Wave2" dense dark class="wave" v-model="wave2"></v-select>
        <v-select :items="event" item-text="title" label="Wave3" dense dark class="wave" v-model="wave3"></v-select>
      </v-col>
      <v-btn :disabled="!valid" class="mr-2" @click="search" dark>Search Seed</v-btn>
    </v-form>
    <v-container class="table">
      <p>Searching: {{ this.seed }} Found: {{ this.seeds.length }}</p>
      <v-data-table :headers="headers" :items="seeds" :items-per-page="20" :mobile-breakpoint="360" dark hide-default-footer dense></v-data-table>
    </v-container>
  </v-container>
</template>

<script>
import { validationMixin } from "vuelidate"
import { required } from 'vuelidate/lib/validators'

class Random {
  constructor() { }

  init(seed) {
    this.mSeed1 = Math.imul(0x6C078965, (seed ^ (seed >>> 30))) + 1;
    this.mSeed2 = Math.imul(0x6C078965, (this.mSeed1 ^ (this.mSeed1 >>> 30))) + 2;
    this.mSeed3 = Math.imul(0x6C078965, (this.mSeed2 ^ (this.mSeed2 >>> 30))) + 3;
    this.mSeed4 = Math.imul(0x6C078965, (this.mSeed3 ^ (this.mSeed3 >>> 30))) + 4;
  }

  getU32() {
    let n = (this.mSeed1 ^ (this.mSeed1 << 11)) >>> 0;
    this.mSeed1 = this.mSeed2;
    this.mSeed2 = this.mSeed3;
    this.mSeed3 = this.mSeed4;
    this.mSeed4 = (n ^ (n >>> 8) ^ this.mSeed4 ^ (this.mSeed4 >>> 19)) >>> 0;

    return this.mSeed4;
  }
}

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

export default {
  mixins: [validationMixin],

  validations: {
    version: { required },
    wave1: { required },
    wave2: { required },
    wave3: { required },
  },

  data: () => ({
    valid: false,
    version: ["3.1.0", "5.3.0"],
    event: [
      {
        title: "LT-NoEvent",
        value: "00"
      },
      {
        title: "NT-NoEvent",
        value: "10"
      },
      {
        title: "HT-NoEvent",
        value: "20"
      },
      {
        title: "NT-Rush",
        value: "11"
      },
      {
        title: "HT-Rush",
        value: "21"
      },
      {
        title: "NT-Goldie Seeking",
        value: "12"
      },
      {
        title: "HT-Goldie Seeking",
        value: "22"
      },
      {
        title: "NT-Griller",
        value: "13"
      },
      {
        title: "HT-Griller",
        value: "23"
      },
      {
        title: "LT-The Mothership",
        value: "04"
      },
      {
        title: "NT-The Mothership",
        value: "14"
      },
      {
        title: "HT-The Mothership",
        value: "24"
      },
      {
        title: "LT-Fog",
        value: "05"
      },
      {
        title: "NT-Fog",
        value: "15"
      },
      {
        title: "HT-Fog",
        value: "25"
      },
      {
        title: "LT-Cohock Charge",
        value: "06"
      },
    ],
    wave1: "",
    wave2: "",
    wave3: "",
    seed: 0,
    maxValue: 0xFFFFFF,
    seeds: [],
    tmp: [],
    headers: [
      {
        text: "Seed",
        value: "value",
        align: "center",
        sortable: false,
      },
      {
        text: "IPSwitch",
        value: "arm64",
        align: "center",
        sortable: false,
      },
    ]
  }),

  methods: {
    async convert(seeds) {
      this.seeds.splice(0, this.seeds.length)
      const url = "https://salmonia.mydns.jp/api/convert"
      const body = {
        seeds: seeds
      }
      const response = await fetch(url, { method: "POST", body: JSON.stringify(body) })
      const arm64 = await response.json()

      // 0xFFFF以下のシードの件数を求める
      const offset = this.tmp.length * 2 - arm64.length
      // console.log(offset, arm64)

      this.tmp.forEach((seed, index) => {
        switch (index < offset) {
          case true:
            this.seeds.push({ value: "0x" + seed.toString(16).toUpperCase(), arm64: "00208C74 " + arm64[index] })
            break
          case false: {
            const idx = offset + (index - offset) * 2
            this.seeds.push({ value: "0x" + seed.toString(16).toUpperCase(), arm64: "00208C74 " + arm64[idx] + "\n 00208C78 " + arm64[idx + 1] })
            break
          }
        }
      });
      return arm64["arm64"]
    },
    async search() {
      // まずは全要素を空っぽにする
      this.tmp.splice(0, this.tmp.length)
      let sWave = this.wave1 + this.wave2 + this.wave3
      const mProb = new Prob()

      for (this.seed = 0x0; this.seed <= this.maxValue && this.tmp.length < 20; ++this.seed) {
        let mWave = new Wave()
        let rnd = new Random();
        rnd.init(this.seed);

        for (let wave = 0; wave < 3; ++wave) {
          for (let event = 0, sum = 0; event < 7; ++event) {
            if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))
              continue;
            sum += mProb.event[event]
            if ((rnd.getU32() * sum / Math.pow(2, 32)) < mProb.event[event])
              mWave.event[wave] = event
          }
          for (let tide = 0, sum = 0; tide < 3; ++tide) {
            if ((tide == 0) && (1 <= mWave.event[wave] && (mWave.event[wave] <= 3)))
              continue;
            sum += mProb.tide[tide];
            if ((rnd.getU32() * sum / Math.pow(2, 32)) < mProb.tide[tide])
              mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide
          }
        }
        const cWave = String(mWave.tide[0]) + String(mWave.event[0]) + String(mWave.tide[1]) + String(mWave.event[1]) + String(mWave.tide[2]) + String(mWave.event[2])
        if (cWave == sWave)
          this.tmp.push(this.seed)
      }
      console.log(this.tmp)
      this.convert(this.tmp)
    }
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
  width: 99%;
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
</style>
