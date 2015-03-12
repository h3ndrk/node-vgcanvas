var fs = require("fs");
var http = require("http");
var https = require("https");
var WeatherWorker = require("./weatherWorker.js");

function Weather(path)
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
			var weatherWorker = new WeatherWorker();
			weatherWorker.request(value, function(weatherData)
			{
				console.log(weatherData);
			});
		});
	});
}

module.exports = Weather;