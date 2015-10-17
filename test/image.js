module.exports.name = "Images";
module.exports.test = function(ctx, w, h) {
	ctx.drawImage(ctx.testImg, 100, 100, 200, 200);
}
