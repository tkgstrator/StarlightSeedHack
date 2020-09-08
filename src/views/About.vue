<template>
  <div class="about">
    <v-container fluid>
      <h1>What's SeedHack</h1>
      <p>SeedHack is the best way to fix waves for Salmon Run in the Shoal. Please make sure the console applying SeedHack must be a host.</p>
      <h1>Contributors</h1>
      <ul>
        <li>
          <a href="https://twitter.com/shadowninja108">shadowninja108</a> - Expertise in Splatoon 2's inner workings
        </li>
        <li>
          <a href="https://twitter.com/container12345">container12345</a> - Reverse engineering for Game::Coop classes
        </li>
      </ul>
      <h1>Source Code</h1>
      <p>Every source code is public on GitHub.</p>
      <highlight-code auto>
        <pre>
        let rnd = new Random();
        rnd.init(this.seed);

        for (let wave = 0; wave &lt; 3; ++wave) {
          for (let event = 0, sum = 0; event &lt; 7; ++event) {
            if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))
              continue;
            sum += mProb.event[event]
            if ((rnd.getU32() * sum / Math.pow(2, 32)) &lt; mProb.event[event])
              mWave.event[wave] = event
          }
          for (let tide = 0, sum = 0; tide &lt; 3; ++tide) {
            if ((tide == 0) && (1 &lt;= mWave.event[wave] && (mWave.event[wave] &lt;= 3)))
              continue;
            sum += mProb.tide[tide];
            if ((rnd.getU32() * sum / Math.pow(2, 32)) &lt; mProb.tide[tide])
              mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide
          }
        }
      </pre>
      </highlight-code>
    </v-container>
  </div>
</template>

<style  scoped>
a {
  color: #ee2200;
  text-decoration: none;
}

ul {
  display: inline-block;
  /* width: 90%; */
}

li {
  text-align: left;
  list-style: none;
}
</style>

<style>
pre {
  display: inline-block;
  /* margin: 0 auto; */
  /* width: 100%; */
  text-align: left !important;
  /* word-break: break-all !important; */
  /* background-color: #111111; */
  /* overflow: normal; */
  /* overflow-wrap: normal; */
  /* overflow: hidden; */
  /* overflow-x: hidden; */
  /* word-wrap: normal; */
  /* white-space: pre; */
}
</style>
