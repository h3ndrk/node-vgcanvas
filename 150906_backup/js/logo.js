function Line(element)
{
	this.element = element;
	this.length = 0;
	
	this.clear = function()
	{
		if(!element)
		{
			return;
		}
		
		var length = element.getTotalLength();
		
		element.style.transition = element.style.WebkitTransition = "none";
		element.style.strokeDasharray = length + " " + length;
		element.style.strokeDashoffset = length;
		element.getBoundingClientRect();
	};
	
	this.draw = function(duration, animation, opacityAnimation)
	{
		if(!element)
		{
			return;
		}
		
		element.style.transition = element.style.WebkitTransition = "stroke-dashoffset " + duration + "s " + animation + ((opacityAnimation)?(", opacity " + duration + "s " + animation):(""));
		element.style.strokeDashoffset = "0";
	};
	
	this.opacity = function(value)
	{
		element.style.opacity = value;
	};
	
	this.hide = function(duration)
	{
		if(!duration)
		{
			duration = 1;
		}
		
		element.style.opacity = 1;
		element.style.transition = element.style.WebkitTransition = "opacity " + duration + "s ease";
		element.style.opacity = 0;
	};
}

var lines = [];

function initLogo()
{
	lines.push(new Line(document.getElementById("line_0")));
	lines.push(new Line(document.getElementById("line_1")));
	lines.push(new Line(document.getElementById("line_2")));
	lines.push(new Line(document.getElementById("line_3")));
	lines.push(new Line(document.getElementById("line_4")));
	lines.push(new Line(document.getElementById("line_5")));
	lines.push(new Line(document.getElementById("line_6")));
	lines.push(new Line(document.getElementById("line_7")));
	lines.push(new Line(document.getElementById("line_8")));
	lines.push(new Line(document.getElementById("line_9")));
	lines.push(new Line(document.getElementById("line_10")));
	lines.push(new Line(document.getElementById("line_11")));
	lines.push(new Line(document.getElementById("line_12")));
	lines.push(new Line(document.getElementById("line_13")));
	lines.push(new Line(document.getElementById("line_14")));
	lines.push(new Line(document.getElementById("line_15")));
	lines.push(new Line(document.getElementById("line_16")));
	lines.push(new Line(document.getElementById("line_17")));
	lines.push(new Line(document.getElementById("circle_0")));
	lines.push(new Line(document.getElementById("circle_1")));
}

function clearLogo()
{
	lines.forEach(function(value, key, array)
	{
		if(key <= 17 && key >= 12)
		{
			value.opacity(0);
		}
		
		value.clear();
	});
}

function drawLogo()
{
	var elementSvg = document.getElementById("svg");
	
	if(!elementSvg)
	{
		return;
	}
	
	elementSvg.style.visibility = "visible";
	
	// circle
	setTimeout(function() { lines[18].opacity(1); lines[18].draw(0.25, "ease-in"); }, 0);
	setTimeout(function() { lines[19].opacity(1); lines[19].draw(0.25, "ease-out"); }, 250);
	setTimeout(function() { lines[18].hide(2); }, 750);
	setTimeout(function() { lines[19].hide(2); }, 750);
	
	// outer hexagon
	setTimeout(function() { lines[5].opacity(1); lines[5].draw(0.25, "ease-in"); }, 500 + 0);
	setTimeout(function() { lines[4].opacity(1); lines[4].draw(0.12, "ease-in"); }, 500 + 250);
	setTimeout(function() { lines[3].opacity(1); lines[3].draw(0.07, "ease-in"); }, 500 + 370);
	setTimeout(function() { lines[2].opacity(1); lines[2].draw(0.15, "ease-out"); }, 500 + 440);
	setTimeout(function() { lines[1].opacity(1); lines[1].draw(0.25, "ease-out"); }, 500 + 590);
	setTimeout(function() { lines[0].opacity(1); lines[0].draw(0.40, "ease-out"); }, 500 + 840);
	
	// inner hexagon
	setTimeout(function() { lines[8].opacity(1); lines[8].draw(0.25, "ease-in"); }, 500 + 250 + 0);
	setTimeout(function() { lines[7].opacity(1); lines[7].draw(0.12, "ease-in"); }, 500 + 250 + 250);
	setTimeout(function() { lines[6].opacity(1); lines[6].draw(0.07, "ease-in"); }, 500 + 250 + 370);
	setTimeout(function() { lines[11].opacity(1); lines[11].draw(0.15, "ease-out"); }, 500 + 250 + 440);
	setTimeout(function() { lines[10].opacity(1); lines[10].draw(0.25, "ease-out"); }, 500 + 250 + 590);
	setTimeout(function() { lines[9].opacity(1); lines[9].draw(0.40, "ease-out"); }, 500 + 250 + 840);
	
	// outer borders
	setTimeout(function() { lines[13].draw(1, "ease-out", true); lines[13].opacity(1); }, 1000 + 0);
	setTimeout(function() { lines[12].draw(1, "ease-out", true); lines[12].opacity(1); }, 1000 + 250);
	setTimeout(function() { lines[14].draw(1, "ease-out", true); lines[14].opacity(1); }, 1000 + 500);
	
	// inner borders
	setTimeout(function() { lines[16].draw(1, "ease-out", true); lines[16].opacity(1); }, 1250 + 0);
	setTimeout(function() { lines[15].draw(1, "ease-out", true); lines[15].opacity(1); }, 1250 + 250);
	setTimeout(function() { lines[17].draw(1, "ease-out", true); lines[17].opacity(1); }, 1250 + 500);
	
	// text
	setTimeout(function()
	{
		var elementH1 = document.getElementById("logoTitle");
		
		if(!elementH1)
		{
			return;
		}
		
		elementH1.style.opacity = 1;
		elementH1.style.visibility = "visible";
	}, 2000);
}

function hideLogo()
{
	lines.forEach(function(value, key, array)
	{
		if(key != 18 && key != 19)
		{
			value.hide();
		}
	});
	
	var elementSvg = document.getElementById("svg");
	var elementH1 = document.getElementById("logoTitle");
	
	if(!elementSvg || !elementH1)
	{
		return;
	}
	
	setTimeout(function() { elementSvg.style.visibility = "hidden"; }, 1000);
	
	setTimeout(function()
	{
		elementH1.style.opacity = 0;
		elementH1.style.visibility = "hidden";
		
		informationsShowNext();
	}, 1500);
}

function posLogo(x, y)
{
	var elementSvg = document.getElementById("svg");
	var elementH1 = document.getElementById("logoTitle");
	
	if(!elementSvg || !elementH1)
	{
		return;
	}
	
	elementSvg.style.top = y + "px";
	elementSvg.style.left = x + "px";
	
	elementH1.style.top = (y + 400) + "px";
	elementH1.style.left = (x + 200 - (elementH1.offsetWidth / 2)) + "px";
}

window.onload = function()
{
	posLogo((window.innerWidth - 400) / 2, (window.innerHeight - 400) / 2);
};

window.onresize = function()
{
	posLogo((window.innerWidth - 400) / 2, (window.innerHeight - 400) / 2);
};