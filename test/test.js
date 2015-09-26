var canvas = require('../lib/canvas')

var ctx = canvas.getContext('2d');

var x = 0;
var y2 = 0, x2 = 0;

setInterval(function() {
	x++;
	y2 = Math.sin(x * 0.1) * 50;
	x2 = Math.cos(x * 0.1) * 50;

	ctx.lineWidth = 10.0;
	ctx.lineCap = 'round';
	ctx.lineJoin = 'round';
	ctx.setLineDash([]);

	ctx.clearRect(0, 0, ctx.getScreenWidth(), ctx.getScreenHeight());

	ctx.fillStyle = '#fff';
	ctx.fillRect(Math.cos(x * 0.01) * ctx.getScreenWidth() / 2 + ctx.getScreenWidth() / 2, 100, 100, 100);

	ctx.fillStyle = '#865656';
	ctx.fillRect(400 + x2, y2 + 400, 100, 100);

	ctx.fillStyle = 'hsla(120, 75%, 75%, .5)';
	ctx.fillRect(550, 700, 100, 100);
	ctx.fillRect(600, 750, 100, 100);

	ctx.strokeStyle = 'cyan';

	ctx.beginPath();
	ctx.moveTo(200, 200);
	ctx.lineTo(100, 100);
	ctx.lineTo(100, 30);
	ctx.stroke();

	ctx.strokeStyle = '#555';
	ctx.strokeRect(700, 50, 150, 75);
	ctx.fillStyle = 'gold';
	ctx.fillRect(700, 50, 150, 75);

	ctx.strokeStyle = 'red';
	ctx.beginPath();
	ctx.moveTo(100, 100);
	ctx.bezierCurveTo(100, 150, 200, 150, 200, 100);
	ctx.stroke();
	
	ctx.lineCap = 'butt';
	ctx.lineWidth = 1.0;
	ctx.lineDashOffset = x;
	ctx.setLineDash([20, 10, 3, 10]);
	ctx.beginPath();
	ctx.arc(800, 900, 100, 0, Math.PI * 0.5, false);
	ctx.lineTo(800, 900);
	ctx.closePath();
	ctx.stroke();
	
	ctx.save();
	ctx.beginPath();
	ctx.arc(200, 900, 100, 0, Math.PI, false);
	ctx.clip();
	
	ctx.fillStyle = 'blue';
	ctx.strokeStyle = 'red';
	ctx.fillRect(100, 800, 200, 200);
	ctx.save();
	
	ctx.beginPath();
	ctx.fillStyle = 'green';
	ctx.strokeStyle = '#fff';
	ctx.arc(150, 850, 20, 0, Math.PI * 2);
	ctx.stroke();
	ctx.fillRect(175, 800, 50, 50);
	ctx.restore();
	
	// red
	ctx.strokeRect(250, 850, 20, 50);
	
	ctx.restore();
	
	// fillStyle: gold
	ctx.fillRect(400, 800, 50, 50);
	
	// red
	ctx.lineWidth = 10;
	ctx.lineCap = 'round';
	ctx.beginPath();
	ctx.setLineDash([30, 30, 80, 30]);
	ctx.arc(500, 500, 200, 0, Math.PI * 2);
	ctx.stroke();

	ctx.swapBuffers();
}, 16);
