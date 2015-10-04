var canvas = require('../lib/canvas')
var tests = [require('./colorPaint'), require('./alpha')];
require('keypress')(process.stdin);

var ctx = canvas.getContext('2d');
ctx.loadFont('./font.ttf', 'font');
var w = ctx.getScreenWidth();
var h = ctx.getScreenHeight();
var current = 0;

function test() {
	if(current == tests.length) {
		console.log('All tests finished');
		ctx.cleanup();
		return process.stdin.pause();
	}
	
	ctx.clearRect(0, 0, w, h);
	ctx.font = '20px font';
	var str = 'Test ' + current + ': ' + tests[current].name;
	console.log(str);
	ctx.fillStyle = '#000';
	ctx.strokeStyle = '#000';
	ctx.fillText(str, 10, 30);
	tests[current].test(ctx, w, h);
	ctx.swapBuffers();
	current++;
}

process.stdin.on('keypress', function(ch, key) {
	if(key && key.name == 'return') {
		test();
	} else if(key && key.name == 'c' && key.ctrl) {
		ctx.cleanup();
		process.stdin.pause();
	}
});

test();
process.stdin.setRawMode(true);
process.stdin.resume();

/*var x = 0;
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
	ctx.font = '50px ./font.ttf';

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
	
	ctx.fillText('Das ist ein Test-TEXT!', 200, 400);
	
	//ctx.save();
	ctx.fillStyle = gradient;
	ctx.fillRect(300, 100, 100, 100);
	//ctx.restore();
	
	ctx.fillStyle = gradient2;
	ctx.fillRect(w / 2 - 500, h / 2 - 500, 1000, 1000);
	
	ctx.swapBuffers();
}, 16);*/
