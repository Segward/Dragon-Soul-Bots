// server.js

const express = require("express");
const app = express();
const HOST = "0.0.0.0";
const PORT = 8000;

let servers = [
  "https://www.roblox.com/share?code=6bedff04407dfe44a45423e8842540a4&type=Server",
  "https://www.roblox.com/share?code=ad96cd66ae5ef346bb4764547c46274a&type=Server",
];

let winConnect = false;
let macConnect = false;
let macServer = null;
let winServer = null;
let request = null;

app.post("/win-connect", (req, res) => {
  winConnect = true;
  res.send("Windows connected");
});

app.post("/mac-connect", (req, res) => {
  macConnect = true;
  res.send("Mac connected");
});

app.post("/win-disconnect", (req, res) => {
  winConnect = false;
  res.send("Windows disconnected");
});

app.post("/mac-disconnect", (req, res) => {
  macConnect = false;
  res.send("Mac disconnected");
});

app.get("/mac-status", (req, res) => {
  res.send(macConnect+"");
});

app.get("/win-status", (req, res) => {
  res.send(winConnect+"");
});

app.post("/mac-join", (req, res) => {
  if (winServer === null || winServer === 1) {
    macServer = 0;
    res.send(servers[macServer]+"");
  } else if (winServer === 0) {
    macServer = 1;
    res.send(servers[macServer]+"");
  }
});

app.post("/win-join", (req, res) => {
  if (macServer === null || macServer === 1) {
    winServer = 0;
    res.send(servers[winServer]+"");
  } else if (macServer === 0) {
    winServer = 1;
    res.send(servers[winServer]+"");
  }
});

app.get("/mac-follow", (req, res) => {
  if (winServer === null) {
    macServer = null;
    res.send("No win server");
  } else {
    macServer = winServer;
    res.send(servers[winServer]+"");
  }
});

app.get("/win-follow", (req, res) => {
  if (macServer === null) {
    winServer = null;
    res.send("No mac server");
  } else {
    winServer = macServer;
    res.send(servers[macServer]+"");
  }
});

app.post("/request-mac-leave", (req, res) => {
  request = "mac-leave";
  res.send("Requesting mac leave");
});

app.post("/request-win-leave", (req, res) => {
  request = "win-leave";
  res.send("Requesting win leave");
});

app.post("/request-mac-join", (req, res) => {
  request = "mac-join";
  res.send("Requesting mac join");
});

app.post("/request-win-join", (req, res) => {
  request = "win-join";
  res.send("Requesting win join");
});

app.get("/get-request", (req, res) => {
  res.send(request+"");
});

app.post("/clear-request", (req, res) => {
  request = null;
  res.send("Request cleared");
});

app.get("/win-joined", (req, res) => {
  const joined = winServer === null ? false : true;
  res.send(joined+"");
});

app.get("/mac-joined", (req, res) => {
  const joined = macServer === null ? false : true;
  res.send(joined+"");
});

app.post("/mac-leave", (req, res) => {
  macServer = null;
  res.send("Mac server left");
});

app.post("/win-leave", (req, res) => {
  winServer = null;
  res.send("Win server left");
});

app.use(express.static("dist"));

app.listen(PORT, HOST, () => {
  console.log(`Server running at http://${HOST}:${PORT}/`);
});
