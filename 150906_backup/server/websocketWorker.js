var WebsocketServer = require("websocket").server;
var http = require("http");
var Client = require("./client.js");

function WebsocketWorker()
{
	this.informations = [];
	this.clients = [];
	
	this.serve = function(port)
	{
		var server = http.createServer(function(request, response)
		{
			response.writeHead(404);
			response.end();
		}).listen(port, function()
		{
			console.log("Serving server... ;)");
		});
		
		var websocketServer = new WebsocketServer({ httpServer: server, autoAcceptConnections: false });
		
		// function originIsAllowed(origin)
		// {
		// 	return true;
		// }
		
		websocketServer.on("request", function(request)
		{
			// if(!originIsAllowed(request.origin))
			// {
			// 	request.reject();
			// 	console.log("Connection rejected: " + request.origin);
			// 	return;
			// }
			
			var connection = request.accept(null, request.origin);
			var client = new Client();
			client.handle(connection);
			client.updateInformations(this.informations);
			client.on("message", function(message)
			{
				console.log("Got message: " + JSON.stringify(message, null, "\t"));
			});
			client.on("close", function()
			{
				console.log("Closed connection");
			});
			this.clients.push(client);
		}.bind(this));
	};
	
	this.updateInformations = function(informations)
	{
		this.informations = informations;
		
		this.clients.forEach(function(value, key, array)
		{
			value.updateInformations(informations);
		});
	};
}

module.exports = WebsocketWorker;