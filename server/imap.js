var fs = require("fs");
var ImapWorker = require("./imapWorker.js");

function Imap(path)
{
	fs.readFile(path, function(error, data)
	{
		if(error)
		{
			console.error(error.message);
			
			return;
		}
		
		var sources = JSON.parse(data.toString());
		
		sources.forEach(function(value, key, array)
		{
			if(value.host && value.port && value.user && value.password && value.boxName && value.tls)
			{
				var imapWorker = new ImapWorker();
				imapWorker.request(value.host, value.port, value.user, value.password, value.boxName, value.tls, function(unreadMessages)
				{
					console.log(unreadMessages);
				});
			}
		});
	});
}

module.exports = Imap;