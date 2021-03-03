module.exports = {
  transpileDependencies: ["vuetify"],
  pages: {
    index: {
      entry: "src/main.js",
      title: "SeedHack",
    },
  },
  // publicPath: process.env.NODE_ENV === "production" ? "/" : "/",
  productionSourceMap: false,
  assetsDir: "",
  outputDir: "./dist",
};
