var fs = require("fs");
var RSSWorker = require("./rssWorker.js");

function RSS(path, callback)
{
	fs.readFile(path, function(error, data)
	{
		if(error)
		{
			console.error(error.message);
			
			return;
		}
		
		var sources = data.toString().split("\n");
		
		sources = sources.filter(function(value, key, array)
		{
			if(value == "")
			{
				return false;
			}
			
			return true;
		});
		
		sources.forEach(function(value, key, array)
		{
			var rssWorker = new RSSWorker();
			rssWorker.request(value, function(title, items)
			{
				items.forEach(function(value, key, array)
				{
					if(callback)
					{
						callback(title, value.title);
					}
				});
				
				callback();
			});
		});
	});
}

module.exports = RSS;