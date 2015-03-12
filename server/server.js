var RSS = require("./rss.js");

var sources = [
	"http://www.heise.de/newsticker/heise-top-atom.xml",
	"http://www.spiegel.de/schlagzeilen/tops/index.rss",
	"http://www.heise.de/security/news/news-atom.xml",
	"http://www.heise.de/developer/rss/news-atom.xml"
];

sources.forEach(function(value, key, array)
{
	var rss = new RSS();
	rss.request(value, function(title, items)
	{
		items.forEach(function(value, key, array)
		{
			console.log(title + ": " + value.title);
		});
	});
});