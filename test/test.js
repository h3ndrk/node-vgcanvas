var canvas = require('../lib/canvas')
var tests = [require('./colorPaint'), require('./alpha'), require('./gradient'), require('./image')];
require('keypress')(process.stdin);

var ctx = canvas.getContext('2d');
ctx.loadFont('./font.ttf', 'font');
var w = ctx.getScreenWidth();
var h = ctx.getScreenHeight();
var current = 0;

var img = new canvas.Image();
img.onload = function() {
	console.log("IMAGE LOADED " + JSON.stringify(img));
}

img.src = 'test.png';
ctx.testImg = img;

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
