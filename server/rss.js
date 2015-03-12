var FeedParser = require("feedparser");
var http = require("http");

function Rss()
{
	this.items = [];
	this.title = "";
	var feedparser = FeedParser();
	
	this.request = function(url, callback)
	{
		// retrieve RSS
		http.get(url, function(res)
		{
			if(res.statusCode != 200)
			{
				return this.emit("error", new Error("Bad status code"));
			}
			
			res.pipe(feedparser);
		}).on("error", function(error)
		{
			if(error)
			{
				console.error(error.message);
			}
		});
		
		// parse RSS
		feedparser.on("error", function(error)
		{
			if(error)
			{
				console.error(error.message);
			}
		});
		feedparser.on("data", function(chunk)
		{
			this.items.push(chunk);
		}.bind(this));
		feedparser.on("end", function()
		{
			if(callback)
			{
				callback();
			}
		}.bind(this));
	};
}

module.exports = Rss;