var informations = [];

function Information(headline, text)
{
	this.headline = headline;
	this.text = text;
	this.hideTimeout = null;
	this.visible = false;
	
	this.element = document.createElement("div");
	this.element.className = "information";
	
	var headlineElement = document.createElement("h1");
	headlineElement.innerHTML = this.headline;
	
	var textElement = document.createElement("p");
	textElement.innerHTML = this.text;
	
	this.element.appendChild(headlineElement);
	this.element.appendChild(textElement);
	
	this.show = function()
	{
		this.visible = true;
		this.element.className = "information show";
		
		this.hideTimeout = setTimeout(this.hide.bind(this), 35000);
	};
	
	this.hide = function()
	{
		clearTimeout(this.hideTimeout);
		
		this.visible = false;
		this.element.className = "information";
	};
}

function informationAdd(headline, text)
{
	var informationsElement = document.getElementById("informations");
	
	if(!informationsElement)
	{
		return;
	}
	
	var information = new Information(headline, text);
	informationsElement.appendChild(information.element);
	informations.push(information);
}

function informationRemove(headline, text)
{
	var removedInformation = null;
	
	informations = informations.filter(function(value, key, array)
	{
		if(value.headline == headline && value.text == text)
		{
			removedInformation = value;
			return false;
		}
		
		return true;
	});
	
	informationsElement.removeChild(removedInformation.element);
}

function shuffle(array)
{
	for(var j, x, i = array.length; i; j = Math.floor(Math.random() * i), x = array[--i], array[i] = array[j], array[j] = x);
	return array;
}

var lastIndex = -1;
function informationsShowNext()
{
	lastIndex = lastIndex + 1;
	
	shuffle(informations);
	
	if(lastIndex == informations.length)
	{
		lastIndex = 0;
	}
	
	if(!informations[lastIndex].visible)
	{
		// informations[lastIndex].element.style.top = (Math.random() * (window.innerHeight - 400) / 2) + "px";
		informations[lastIndex].element.style.left = (Math.random() * (window.innerWidth - informations[lastIndex].element.offsetWidth)) + "px";
		informations[lastIndex].show();
	}
	
	setTimeout(informationsShowNext, Math.random() * 1000 + 2000)
}