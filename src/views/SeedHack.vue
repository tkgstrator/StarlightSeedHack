<template>
  <v-container fluid>
    <v-form v-model="valid" lazy-validation ref="form">
      <v-col class="d-flex" cols="6" sm="12">
        <v-select :items="version" label="Version" dense dark></v-select>
        <v-select :items="version" label="Options" dense dark></v-select>
      </v-col>
      <v-col class="d-flex">
        <v-select :items="event" item-text="title" label="Wave1" dense dark class="wave" v-model="wave1"></v-select>
        <v-select :items="event" item-text="title" label="Wave2" dense dark class="wave" v-model="wave2"></v-select>
        <v-select :items="event" item-text="title" label="Wave3" dense dark class="wave" v-model="wave3"></v-select>
      </v-col>
      <v-btn :disabled="!valid" color="success" class="mr-4" @click="search" dark>Search Seed</v-btn>
    </v-form>
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

class SeedHack {
  constructor() {
    this.maxValue = 5
  }

  search() {
    let mProb = new Prob()

    for (let seed = 0; seed <= this.maxValue; ++seed) {
      let mWave = new Wave()
      let rnd = new Random();
      rnd.init(seed);

      for (let wave = 0; wave < 3; ++wave) {
        for (let event = 0, sum = 0; event < 7; ++event) {
          if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))
            continue;
          sum += mProb.event[event]
          if ((rnd.getU32() * sum / Math.pow(2, 0x20)) < mProb.event[event])
            mWave.event[wave] = event
        }
        for (let tide = 0, sum = 0; tide < 3; ++tide) {
          if ((tide == 0) && (1 <= mWave.event[wave] && (mWave.event[wave] <= 3)))
            continue;
          sum += mProb.tide[tide];
          if ((rnd.getU32() * sum / Math.pow(2, 0x20)) < mProb.tide[tide])
            mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide
        }
      }
      console.log(mWave.event, mWave.tide)
    }
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
        title: "NT-Goldie Seeking",
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
    wave3: ""
  }),
  methods: {
    search() {
      console.log("SEARCH", this.wave1, this.wave2, this.wave3)
      let seedhack = new SeedHack()
      seedhack.search()
    }
  }
}

</script>

<style>
.container {
  font-family: "Splatfont";
  color: #eeeeee;
}

body {
  margin: 0 auto;
  background-color: #111111;
  width: 90%;
}

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
  width: 30%;
}
</style>
