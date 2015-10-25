var vgcanvas = require('../build/Release/vgcanvas');
var VGContext = require('./context');

module.exports.Canvas = function() {
	this.width = 0;
	this.height = 0;
};

module.exports.Canvas.prototype.getContext = function(type) {
	switch(type) {
		case '2d':
			var ctx = new VGContext();
			this.width = ctx.getScreenWidth();
			this.height = ctx.getScreenHeight();
			return ctx;
		default:
			return null;
	}
};

module.exports.Image = vgcanvas.Image;
module.exports.ImageData = require('./imageData');
