var Rss = require("./rss.js");

var rss = new Rss();
rss.request("http://www.heise.de/newsticker/heise-top-atom.xml", function()
{
	console.log(rss.items[0].meta.title);
	// rss.items.forEach(function(value, key, array)
	// {
	// 	console.log(value.title);
	// });
});