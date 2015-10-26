var fs = require('fs');

module.exports.name = "Text";
module.exports.test = function(ctx, w, h) {
	
	ctx.fillText("Text1", 100, 200);
	var metrics = ctx.measureText("Text1");
	ctx.font = '10px font';
	ctx.fillText("width: " + Math.round(metrics.width) + " pixels", 100, 220);
	ctx.fillRect(100, 230, metrics.width, 5);
	
	ctx.font = '50px font';
	ctx.fillText("Larger text", 100, 300);
	metrics = ctx.measureText("Larger text");
	ctx.font = '10px font';
	ctx.fillText("width: " + Math.round(metrics.width) + " pixels", 100, 340);
	ctx.fillRect(100, 350, metrics.width, 5);

	var pattern = ctx.createPattern(ctx.testImg, 'repeat');
	
	ctx.strokeStyle = pattern;
	ctx.font = '70px font';
	ctx.lineWidth = 3;
	ctx.strokeText('pattern stroke', 400, 500);
	ctx.fillStyle = pattern;
	ctx.fillText('pattern fill', 500, 600);
	
	ctx.fillStyle = 'rgba(200, 100, 50, 255)';
	ctx.fillRect(0, 0, 1, 1);
	
	var idata = ctx.getImageData(0, 0, 2, 1);
	var data = idata.data;
	ctx.font = '20px font';
	ctx.fillStyle = 'black';
	ctx.fillText('pixels at (0-1, 1): ' + JSON.stringify(data), 100, 800);
	
	for(var i = 0; i < 20; i++) {
		for(var u = 0; u < 20; u++) {
			ctx.putImageData(idata, 100 + i, 850 + u);
		}
	}
	
	var data2 = ctx.getImageData(400, 450, 100, 100);
	ctx.putImageData(data2, 400, 900);
	
	/*ctx.canvas.toBlob(function(blob) {
		console.log('blobbed');
		
		fs.writeFile('/tmp/test.png', blob);
	});*/
	
	fs.writeFile('/tmp/test2', ctx.canvas.toDataURL());

}
