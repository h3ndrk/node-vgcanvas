function WebsocketConnection(url)
{
	this.url = url;
	
	this.connect = function()
	{
		var connection = new WebSocket(this.url);
		connection.onopen = function()
		{
			initLogo();
			clearLogo();
			drawLogo();
			setTimeout(function() { hideLogo(); }, 5000);
			// console.log("Connection open");
			// connection.send("Das ist ein Test!");
			// setTimeout(function() { connection.close(); }, 10000);
		};
		connection.onmessage = function(event)
		{
			var message = JSON.parse(event.data);
			// console.log("Received message: " + message);
			
			switch(message.command)
			{
				case "addInformation":
				{
					informationAdd(message.data.headline, message.data.text);
					break;
				}
				case "removeInformation":
				{
					informationRemove(message.data.headline, message.data.text);
					break;
				}
				default:
				{
					console.error("Unknown command");
					break;
				}
			}
		};
		// connection.onclose = function(event)
		// {
		// 	console.log("Connection closed");
		// };
		connection.onerror = function(error)
		{
			if(error)
			{
				console.log(error);
			}
		};
	};
}