const express = require("express");
const path = require("path");

const server = express();
const tmpFolder = path.resolve(__dirname, "..", ".pio", "build", "esp01_1m");

console.log(tmpFolder, __dirname);

server.use("/file", express.static(tmpFolder));

server.listen(3333, () => {
  console.log("Server started on port 3333!");
});
