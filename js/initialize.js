var failed = false;

var canvasParticles = null;
var canvasParticlesContext = null;

var canvasBackground = null;
var canvasBackgroundContext = null;

var width = 1280;
var height = 720;

function initialize()
{
	if(!document.getElementById("canvasParticles") || !document.getElementById("canvasBackground"))
	{
		console.error("Failed to find canvas elements.");
		failed = true;
		return;
	}
	
	canvasParticles = document.getElementById("canvasParticles");
	canvasBackground = document.getElementById("canvasBackground");
	
	if(!canvasParticles.getContext || !canvasBackground.getContext)
	{
		console.error("Failed to get canvas contexts.");
		failed = true;
		return;
	}
	
	canvasParticles.width = width;
	canvasBackground.width = width;
	canvasParticles.height = height;
	canvasBackground.height = height;
	
	canvasParticlesContext = canvasParticles.getContext("2d");
	canvasBackgroundContext = canvasBackground.getContext("2d");
}

function render()
{
	if(failed)
	{
		return;
	}
	
	particlesRender();
	backgroundRender();
}

window.onload = function()
{
	initialize();
	render();
};