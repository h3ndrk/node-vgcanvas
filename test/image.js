module.exports.name = "Images";
module.exports.test = function(ctx, w, h) {
	ctx.imageSmootingEnabled = true;
	ctx.drawImage(ctx.testImg, 100, 100, 200, 200);
	
	ctx.imageSmootingEnabled = false;
	ctx.drawImage(ctx.testImg, 400, 100, 200, 200);
}
