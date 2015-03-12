var Imap = require("imap");

function ImapWorker()
{
	this.unreadMessages = [];
	
	this.request = function(host, port, user, password, boxName, tls, callback)
	{
		var imap = new Imap(
		{
			user: user,
			password: password,
			host: host,
			port: port,
			tls: tls
		});
		
		imap.once("ready", function()
		{
			imap.openBox(boxName, true, function(error, box)
			{
				if(error)
				{
					console.log(error.message);
					
					return;
				}
				
				imap.search(["UNSEEN"], function(error, results)
				{
					if(results.length > 0)
					{
						var command = imap.fetch(results, { bodies: "" });
						command.on("message", function(message, seqno)
						{
							message.on("body", function(stream, info)
							{
								var body = "";
								stream.on("data", function(chunk)
								{
									body += chunk.toString();
								});
								stream.on("error", function(error)
								{
									if(error)
									{
										console.error(error.message);
										
										return;
									}
								});
								stream.on("end", function()
								{
									var parsedHeader = Imap.parseHeader(body);
									this.unreadMessages.push({ subject: parsedHeader.subject[0], from: parsedHeader.from[0], date: parsedHeader.date[0] });
								}.bind(this));
							}.bind(this));
						}.bind(this));
						command.on("error", function(error)
						{
							if(error)
							{
								console.error(error.message);
								
								return;
							}
						});
						command.on("end", function()
						{
							if(callback)
							{
								callback(this.unreadMessages);
							}
							
							imap.closeBox(function()
							{
								imap.destroy();
								imap.end();
							});
						}.bind(this));
					}
					else
					{
						console.log("No new unread messages");
						
						imap.closeBox(function()
						{
							imap.destroy();
							imap.end();
						});
					}
				}.bind(this))
			}.bind(this));
		}.bind(this));
		
		imap.on("error", function(error)
		{
			if(error)
			{
				console.log(error.message);
				
				return;
			}
		});
		
		imap.connect();
	}
}

module.exports = ImapWorker;