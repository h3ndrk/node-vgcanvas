var WebsocketServer = require("websocket").server;
var http = require("http");

function Websocket()
{
	this.serve = function(port, callback)
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
			if(connection && callback)
			{
				callback(connection);
			}
		});
	};
}

module.exports = Websocket;