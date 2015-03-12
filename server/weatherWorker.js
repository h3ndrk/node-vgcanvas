var FeedParser = require("feedparser");
var http = require("http");
var https = require("https");
var Iconv = require("iconv").Iconv;
var checkHTTPS = require("./checkHTTPS.js");

function WeatherWorker()
{
	this.request = function(url, callback)
	{
		// retrieve RSS, support for HTTP and HTTPS
		if(checkHTTPS(url))
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
				
				response.on("data", function(chunk)
				{
					if(callback)
					{
						callback(JSON.parse(chunk.toString()));
					}
				});
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
				
				response.on("data", function(chunk)
				{
					if(callback)
					{
						callback(JSON.parse(chunk.toString()));
					}
				});
			}).on("error", function(error)
			{
				if(error)
				{
					console.error(error.message);
				}
			});
		}
	};
}

module.exports = WeatherWorker;