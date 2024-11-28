// server.js

const express = require("express");
const app = express();
const HOST = "0.0.0.0";
const PORT = 8000;

let winConnect = false;
let macConnect = false;
let macServer = null;
let winServer = null;
let servers = [
  "https://www.roblox.com/share?code=6bedff04407dfe44a45423e8842540a4&type=Server",
  "https://www.roblox.com/share?code=ad96cd66ae5ef346bb4764547c46274a&type=Server",
];

app.post("/win-connect", (req, res) => {
  winConnect = true;
  res.send("Windows connected\n");
});

app.post("/mac-connect", (req, res) => {
  macConnect = true;
  res.send("Mac connected\n");
});

app.get("/mac-status", (req, res) => {
  res.send(macConnect + "\n");
});

app.get("/win-status", (req, res) => {
  res.send(winConnect + "\n");
});

app.get("/mac-join", (req, res) => {
  if (winServer === null || winServer === 1) {
    macServer = 0;
    res.send(servers[macServer] + "\n");
  } else if (winServer === 0) {
    macServer = 1;
    res.send(servers[macServer] + "\n");
  }
});

app.get("/win-join", (req, res) => {
  if (macServer === null || macServer === 1) {
    winServer = 0;
    res.send(servers[winServer] + "\n");
  } else if (macServer === 0) {
    winServer = 1;
    res.send(servers[winServer] + "\n");
  }
});

app.get("/mac-follow", (req, res) => {
  if (winServer === null) {
    macServer = null;
    res.send("No win server\n");
  } else {
    macServer = winServer;
    res.send(servers[winServer] + "\n");
  }
});

app.get("/win-follow", (req, res) => {
  if (macServer === null) {
    winServer = null;
    res.send("No mac server\n");
  } else {
    winServer = macServer;
    res.send(servers[macServer] + "\n");
  }
});

app.post("/mac-leave", (req, res) => {
  macServer = null;
  res.send("Mac server left \n");
});

app.post("/win-leave", (req, res) => {
  winServer = null;
  res.send("Win server left \n");
});

app.use(express.static("dist"));

app.listen(PORT, HOST, () => {
  console.log(`Server running at http://${HOST}:${PORT}/`);
});
