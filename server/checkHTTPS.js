function checkHTTPS(url)
{
	if(url.substring(0, 5) == "https")
	{
		return true;
	}
	
	return false;
}

module.exports = checkHTTPS;