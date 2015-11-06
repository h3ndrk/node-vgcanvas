var vgcanvas = require('../build/Release/vgcanvas');
var VGContext = require('./context');

module.exports.Canvas = function() {
	this.width = 0;
	this.height = 0;
	this.funcs = {};
};

module.exports.Canvas.prototype.getContext = function(type) {
	switch(type) {
		case '2d':
			var ctx = new VGContext(this);
			this._ctx = ctx;
			this.width = ctx.getScreenWidth();
			this.height = ctx.getScreenHeight();
			return ctx;
		default:
			return null;
	}
};

module.exports.Canvas.prototype.toBlob = function(cb, type, encoder) {
	if(type === undefined || encoder === undefined) {
		type = "image/png";
		encoder = 1;
	}
	
	this._ctx.toBlob(cb, type, encoder);
};

module.exports.Canvas.prototype.toDataURL = function(type, encoder) {
	if(type === undefined || encoder === undefined) {
		type = "image/png";
		encoder = 1;
	}
	
	return this._ctx.toDataURL(type, encoder);
};

module.exports.Canvas.prototype.requestAnimationFrame = function(cb) {
	var empty = true;
	for(var key in this.funcs) {
		empty = false;
	}
	
	if(empty) {
		setTimeout(this._ctx._loop.bind(this._ctx), 0);
	}
	
	var id = Math.floor(Math.random() * 1e9);
	this.funcs[id] = cb;
	return id;
};

module.exports.Canvas.prototype.cancelAnimationFrame = function(id) {
	delete this.funcs[id];
};


module.exports.Image = vgcanvas.Image;
module.exports.ImageData = require('./imageData');
