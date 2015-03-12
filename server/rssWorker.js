var FeedParser = require("feedparser");
var http = require("http");
var https = require("https");
var Iconv = require("iconv").Iconv;

function RSS()
{
	var items = [];
	var feedparser = FeedParser();
	
	this.request = function(url, callback)
	{
		// retrieve RSS, support for HTTP and HTTPS
		if(url.substring(0, 5) == "https")
		{
			https.get(url, function(response)
			{
				if(response.statusCode != 200)
				{
					return this.emit("error", new Error("Bad status code: " + url + " responsed error " + response.statusCode));
				}
				
				// convert encodings to utf-8
				var charset = null;
				var iconv = null;
				if(response.headers["content-type"])
				{
					charset = response.headers["content-type"].split(";")[1].trim().replace("charset=", "");
					if(typeof charset == "string")
					{
						if(!/utf-*8/i.test(charset))
						{
							try
							{
								iconv = new Iconv(charset, "utf-8");
								console.log("Converting from " + charset + " to utf-8");
								response = response.pipe(iconv);
							}
							catch(error)
							{
								response.emit("error", error);
							}
						}
					}
				}
				
				response.pipe(feedparser);
			}).on("error", function(error)
			{
				if(error)
				{
					console.error(error.message);
				}
			});
		}
		else
		{
			http.get(url, function(response)
			{
				if(response.statusCode != 200)
				{
					return this.emit("error", new Error("Bad status code: " + url + " responsed error " + response.statusCode));
				}
				
				// convert encodings to utf-8
				var charset = null;
				var iconv = null;
				if(response.headers["content-type"])
				{
					charset = response.headers["content-type"].split(";")[1].trim().replace("charset=", "");
					if(typeof charset == "string")
					{
						if(!/utf-*8/i.test(charset))
						{
							try
							{
								iconv = new Iconv(charset, "utf-8");
								console.log("Converting from " + charset + " to utf-8");
								response = response.pipe(iconv);
							}
							catch(error)
							{
								response.emit("error", error);
							}
						}
					}
				}
				
				response.pipe(feedparser);
			}).on("error", function(error)
			{
				if(error)
				{
					console.error(error.message);
				}
			});
		}
		
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
			items.push(chunk);
		});
		feedparser.on("end", function()
		{
			if(callback)
			{
				callback(items[0].meta.title, items);
			}
		}.bind(this));
	};
}

module.exports = RSS;