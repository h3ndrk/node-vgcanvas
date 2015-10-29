var vgcanvas = require('../build/Release/vgcanvas');

module.exports = function(array, w, h) {
	if(array instanceof Uint8ClampedArray) {
		var length = array.length;
		if(length === 0 || length % 4 !== 0) {
			throw new Error('length is either zero or not a multiple of four');
		}
		
		length /= 4;
		if(length % w !== 0) {
			throw new Error('length is not a multiple of width');
		}
		
		var sh = length / w;
		if(h !== undefined && sh !== h) {
			throw new Error('height is not equals length / width (is: ' + h + ' expected: ' + sh + ')');
		}
		
		// this is no copy
		this.data = array;
		this.width = w;
		this.height = sh;
	} else {
		//array is now width and width height
		
		if(array === 0 || w === 0) {
			throw new Error('width or height is zero');
		}
		
		this.width = array;
		this.height = w;
		this.data = new Uint8ClampedArray(array * w * 4);
	}
	
	this._image = new vgcanvas.Image();
	this._image.setData(this.data, this.width, this.height);
}

module.exports.prototype.update = function() {
	this._image.setData(this.data, this.width, this.height);
}
