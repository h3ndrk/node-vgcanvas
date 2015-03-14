var RSS = require("./rss.js");
var WebsocketWorker = require("./websocketWorker.js");

function Websocket()
{
	var websocketWorker = new WebsocketWorker();
	websocketWorker.serve(8080);
	var informations = [];
	
	RSS("rss.sources", function(headline, text)
	{
		if(!headline && !text)
		{
			websocketWorker.updateInformations(informations);
		}
		
		informations.push({ headline: headline, text: text });
	});
	
	// websocketWorker.updateInformations([
	// 	{
	// 		headline: "Headline 1",
	// 		text: "Text1",
	// 	},
	// 	{
	// 		headline: "Headline 2",
	// 		text: "Text2"
	// 	},
	// 	{
	// 		headline: "Headline 3",
	// 		text: "Text3"
	// 	}
	// ]);
	// setTimeout(function() { websocketWorker.updateInformations(["d", "e", "c"]); }, 3000);
}

module.exports = Websocket;

Websocket();