var imageDarkEdges = null;

var tempContext = null;
var tempRadialGradient = null;

// generate background gradient
function backgroundGenDarkEdges()
{
	imageDarkEdges = document.createElement("canvas");
	imageDarkEdges.width = width;
	imageDarkEdges.height = height;
	
	tempContext = imageDarkEdges.getContext("2d");
	tempRadialGradient = tempContext.createRadialGradient(width / 2, height / 2, width / 2 * 1.1, width / 2, height / 2, 0);
	tempRadialGradient.addColorStop(0, "#000000");
	tempRadialGradient.addColorStop(1, "#FFFFFF");
	tempContext.fillStyle = tempRadialGradient;
	tempContext.fillRect(0, 0, width, height);
}

function backgroundRender()
{
	if(failed)
	{
		return;
	}
	
	// generate background gradient
	if(!imageDarkEdges)
	{
		backgroundGenDarkEdges();
	}
	
	canvasBackgroundContext.clearRect(0, 0, width, height);
	
	// white background
	canvasBackgroundContext.fillStyle = "#FFFFFF";
	canvasBackgroundContext.fillRect(0, 0, width, height);
	
	// background gradient
	canvasBackgroundContext.globalAlpha = 0.5;
	canvasBackgroundContext.drawImage(imageDarkEdges, 0, 0);
	
	requestAnimationFrame(backgroundRender);
}