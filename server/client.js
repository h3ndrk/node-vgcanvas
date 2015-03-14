var WebsocketServer = require("websocket").server;
var EventEmitter = require("events").EventEmitter;
var util = require("util");

function Client()
{
	this.informations = [];
	this.connection = null;
	
	this.handle = function(connection)
	{
		this.connection = connection;
		
		this.connection.on("message", function(message)
		{
			this.emit("message", message);
		}.bind(this));
		this.connection.on("close", function(reasonCode, description)
		{
			this.emit("close");
		}.bind(this));
	};
	
	this.send = function(information)
	{
		this.connection.sendUTF(information);
	};
	
	this.updateInformations = function(informations)
	{
		console.log(informations);
		
		// send removed informations
		this.informations = this.informations.filter(function(value, key, array)
		{
			if(informations.indexOf(value) == -1)
			{
				// console.log("REMOVE: " + value);
				this.send(JSON.stringify({ command: "removeInformation", data: value }));
				return false;
			}
			
			return true;
		}.bind(this));
		
		// send added informations
		informations.forEach(function(value, key, array)
		{
			if(this.informations.indexOf(value) == -1)
			{
				// console.log("ADD: " + value);
				this.send(JSON.stringify({ command: "addInformation", data: value }));
				this.informations.push(value);
			}
		}.bind(this));
	};
}

util.inherits(Client, EventEmitter);

module.exports = Client;