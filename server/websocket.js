var WebsocketWorker = require("./websocketWorker.js");

function Websocket()
{
	var websocketWorker = new WebsocketWorker();
	websocketWorker.serve(8080);
	websocketWorker.updateInformations(["a", "b", "c"]);
	setTimeout(function() { websocketWorker.updateInformations(["d", "e", "c"]); }, 3000);
}

module.exports = Websocket;

Websocket();