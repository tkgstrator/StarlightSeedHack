<template>
  <v-app>
    <div class="home">
      <SeedHack />
    </div>
  </v-app>
</template>

<script>
import SeedHack from "./Search"

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
  /* padding: 0 10 10 10; */
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
