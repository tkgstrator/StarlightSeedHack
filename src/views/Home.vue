<template>
  <v-app>
    <div class="home">
      <h1>What's SeedHack</h1>
      <p>SeedHack is the best way to fix waves for Salmon Run in the Shoal. Please make sure the console applying SeedHack must be a host.</p>
      <SeedHack />
    </div>
  </v-app>
</template>

<script>
import SeedHack from "./SeedHack"

export default {
  name: "App",
  components: {
    SeedHack
  }
}
</script>

<style>
#app {
  font-family: "Splatfont";
  background-color: #111111;
  color: #eeeeee;
}

body {
  margin: 0 auto;
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
</style>
