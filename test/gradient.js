module.exports.name = "Gradients";

module.exports.test = function(ctx, w, h) {
	var gr1 = ctx.createLinearGradient(0, 0, 0, 100);
	gr1.addColorStop(0, 'red');
	gr1.addColorStop(1, 'green');
	ctx.fillStyle = 'red';
	ctx.font = '100px font';
	ctx.fillText('Linear', 0, 0);
}
