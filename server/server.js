var RSS = require("./rss.js");
var Weather = require("./weather.js");
var Imap = require("./imap.js");

RSS("rss.sources");
Weather("weather.source");
Imap("imap.json");