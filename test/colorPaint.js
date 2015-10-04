module.exports.name = 'color paint';

module.exports.test = function(ctx, w, h) {
	ctx.fillText('fill #f00', 100, 100);
	ctx.fillStyle = '#f00';
	ctx.fillRect(100, 150, 100, 100);
	
	ctx.fillStyle = '#000';
	ctx.fillText('stroke #10f045', 300, 100);
	ctx.strokeStyle = '#10f045';
	ctx.strokeRect(300, 150, 100, 100);
}
