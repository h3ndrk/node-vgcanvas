var canvas = require('../lib/canvas')

var ctx = canvas.getContext('2d');

var x = 0;
var y2 = 0, x2 = 0;
var gradient = ctx.createLinearGradient(300, 0, 400, 0);
var gradient2 = ctx.createRadialGradient(750, 950, 50, 750, 950, 0);
gradient.addColorStop(0, 'black');
gradient.addColorStop(1, 'red');

gradient2.addColorStop(0, 'blue');
gradient2.addColorStop(1, 'rgba(0, 0, 0, 0)');

setInterval(function() {
	x++;
	y2 = Math.sin(x * 0.1) * 50;
	x2 = Math.cos(x * 0.1) * 50;

	ctx.clearRect(0, 0, ctx.getScreenWidth(), ctx.getScreenHeight());

	ctx.fillStyle = 'red';
	ctx.fillRect(500, 900, 100, 100);
	
	//ctx.save();
	ctx.fillStyle = gradient;
	ctx.fillRect(300, 900, 100, 100);
	//ctx.restore();
	
	ctx.fillStyle = gradient2;
	ctx.fillRect(700, 900, 100, 100);
	
	ctx.swapBuffers();
}, 16);
