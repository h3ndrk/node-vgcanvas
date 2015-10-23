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
	
	ctx.strokeStyle = 'blue';
	ctx.font = '100px font';
	ctx.strokeText('blue stroke', 400, 500);
}
