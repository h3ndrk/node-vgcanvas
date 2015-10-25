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
		
		if(array === 0 || width === 0) {
			throw new Error('width or height is zero');
		}
		
		this.width = array;
		this.height = width;
		this.data = new Uint8ClampedArray(array * width * 4);
	}
	
	this._image = new vgcanvas.Image();
	this._image.setData(this.data, w, h);
}
