module.exports.name = "Images";
module.exports.test = function(ctx, w, h) {
	ctx.imageSmootingEnabled = true;
	ctx.drawImage(ctx.testImg, 100, 100, 200, 200);
	
	ctx.imageSmootingEnabled = false;
	ctx.drawImage(ctx.testImg, 400, 100, 200, 200);
	
	ctx.fillText('Pattern', 100, 400);
	var pattern = ctx.createPattern(ctx.testImg, 'repeat');
	ctx.fillStyle = pattern;
	
	ctx.fillRect(100, 500, 400, 400);
	
	var data = ctx.createImageData(50, 50);
	for(var x = 0; x < 50; x++) {
		for(var y = 0; y < 50; y++) {
			for(var i = 0; i < 4; i++) {
				data.data[(50 * y + x) * 4 + i] = Math.random() * 255;
			}
		}
	}
	data.update();
	ctx.putImageData(data, 700, 600, 0, 0, 300, 300);
}
