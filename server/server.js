var FeedParser = require("feedparser");
var http = require("http");

var feedparser = FeedParser();

http.get("http://www.heise.de/newsticker/heise-top-atom.xml", function(res)
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

feedparser.on("error", function(error)
{
	if(error)
	{
		console.error(error.message);
	}
});
feedparser.on("readable", function()
{
	var item = null;
	while(item = this.read())
	{
		console.log(item);
	}
});