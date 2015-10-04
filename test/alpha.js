module.exports.name = 'alpha';

module.exports.test = function(ctx, w, h) {
	ctx.fillText('rgba(255, 0, 0, .5)', 100, 100);
	ctx.fillText('rgba(0, 0, 255, .5)', 400, 100);
	
	ctx.fillStyle = 'rgba(255, 0, 0, .5)';
	ctx.fillRect(100, 150, 300, 100);
	ctx.fillStyle = 'rgba(0, 0, 255, .5)';
	ctx.fillRect(300, 150, 300, 100);
};
