var canvas = require('../lib/canvas')

var ctx = canvas.getContext('2d');
var w = ctx.getScreenWidth();
var h = ctx.getScreenHeight();

var x = 0;
var y2 = 0, x2 = 0;
var gradient = ctx.createLinearGradient(300, 0, 400, 0);
var gradient2 = ctx.createRadialGradient(w / 2, h / 2, 500, w / 2, h / 2, 0);
gradient.addColorStop(0, 'black');
gradient.addColorStop(1, 'red');

gradient2.addColorStop(0, 'blue');
gradient2.addColorStop(1, 'rgba(0, 0, 0, 0)');

setInterval(function() {
	x++;
	y2 = Math.sin(x * 0.1) * 50;
	x2 = Math.cos(x * 0.1) * 50;

	ctx.clearRect(0, 0, ctx.getScreenWidth(), ctx.getScreenHeight());

	ctx.strokeStyle = 'green';
	ctx.fillStyle = 'red';
	ctx.lineCap = 'round';
	ctx.setLineDash([10, 20]);
	ctx.lineWidth = 5;
	
	ctx.fillRect(100, 100, 100, 100);
	
	ctx.beginPath();
	ctx.moveTo(100, 250);
	ctx.lineTo(200, 300);
	ctx.lineTo(250, 250);
	ctx.closePath();
	ctx.fill();
	ctx.stroke();
	
	//ctx.save();
	ctx.fillStyle = gradient;
	ctx.fillRect(300, 100, 100, 100);
	//ctx.restore();
	
	ctx.fillStyle = gradient2;
	ctx.fillRect(w / 2 - 500, h / 2 - 500, 1000, 1000);
	
	ctx.swapBuffers();
}, 16);
