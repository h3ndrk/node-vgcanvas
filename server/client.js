var WebsocketServer = require("websocket").server;
var EventEmitter = require("events").EventEmitter;
var util = require("util");

function Client()
{
	this.informations = [];
	
	this.handle = function(connection)
	{
		connection.on("message", function(message)
		{
			this.emit("message", message);
		}.bind(this));
		connection.on("close", function(reasonCode, description)
		{
			this.emit("close");
		}.bind(this));
	};
	
	this.send = function(information)
	{
		connection.sendUTF(information);
	};
}

util.inherits(Client, EventEmitter);

module.exports = Client;