var RSS = require("./rss.js");
var Weather = require("./weather.js");
var Imap = require("./imap.js");
var Websocket = require("./websocket.js");
var Client = require("./client.js");

// RSS("rss.sources");
// Weather("weather.source");
// Imap("imap.json");

var websocket = new Websocket();
websocket.serve(8080, function(connection)
{
	var client = new Client();
	client.handle(connection);
	client.on("message", function(message)
	{
		console.log("Got message: " + JSON.stringify(message, null, "\t"));
	});
	client.on("close", function()
	{
		console.log("Closed connection");
	});
});