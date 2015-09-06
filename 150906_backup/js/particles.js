function particlesRender()
{
	if(failed)
	{
		return;
	}
	
	canvasParticlesContext.clearRect(0, 0, width, height);
	
	// render a red square at random location
	canvasParticlesContext.fillStyle = "#FF0000";
	canvasParticlesContext.fillRect(Math.round(Math.random() * 1260), Math.round(Math.random() * 695), 25, 25);
	
	requestAnimationFrame(particlesRender);
}