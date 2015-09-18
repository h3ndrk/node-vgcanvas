var vgcanvas = require('../build/Release/vgcanvas');
var color = require('onecolor');

var VGContext = function() {
	var self = this;

	vgcanvas.init();

	Object.defineProperty(this, "fillStyle", {
		set: function(value) {
			self.setFillStyle(color(value));
			self.fillStyleValue = value;
		},
		get: function() {
			var ar = vgcanvas.getFillStyle();
			return 'rgba(' + ar[0] * 0xFF + ', ' + ar[1] * 0xFF + ', ' + ar[2] * 0xFF + ', ' + ar[3] + ')';
		}
	});

	Object.defineProperty(this, "strokeStyle", {
		set: function(value) {
			self.setStrokeStyle(color(value));
			self.strokeStyleValue = value;
		},
		get: function() {
			var ar = vgcanvas.getStrokeStyle();
			return 'rgba(' + ar[0] * 0xFF + ', ' + ar[1] * 0xFF + ', ' + ar[2] * 0xFF + ', ' + ar[3] + ')';
		}
	});

	Object.defineProperty(this, "lineWidth", {
		set: vgcanvas.setLineWidth,
		get: vgcanvas.getLineWidth
	});

	Object.defineProperty(this, "lineCap", {
		set: vgcanvas.setLineCap,
		get: vgcanvas.getLineCap
	});

	Object.defineProperty(this, "lineJoin", {
		set: vgcanvas.setLineJoin,
		get: vgcanvas.getLineJoin
	});
	
	Object.defineProperty(this, "lineDashOffset", {
		set: vgcanvas.setLineDashOffset,
		get: vgcanvas.getLineDashOffset
	});
	
	Object.defineProperty(this, "globalAlpha", {
		set: vgcanvas.setGlobalAlpha,
		get: vgcanvas.getGlobalAlpha
	});
};

VGContext.prototype.setFillStyle = function(color) {
	vgcanvas.setFillStyle(color.red(), color.green(), color.blue(), color.alpha());
}

VGContext.prototype.setStrokeStyle = function(color) {
	vgcanvas.setStrokeStyle(color.red(), color.green(), color.blue(), color.alpha());
}

VGContext.prototype.setLineWidth = vgcanvas.setLineWidth;
VGContext.prototype.setLineCap = vgcanvas.setLineCap;
VGContext.prototype.setLineJoin = vgcanvas.setLineJoin;
VGContext.prototype.setLineDash = function(data) {
	if(data.length % 2 != 0)
		data = data.concat(data);
		
	this.lineDash = data;
	
	vgcanvas.setLineDash(data);
}
VGContext.prototype.setLineDashOffset = vgcanvas.setLineDashOffset;
VGContext.prototype.getLineDash = vgcanvas.getLineDash;

VGContext.prototype.fillRect = vgcanvas.fillRect;
VGContext.prototype.clearRect = vgcanvas.clearRect;
VGContext.prototype.strokeRect = vgcanvas.strokeRect;

VGContext.prototype.beginPath = vgcanvas.beginPath;
VGContext.prototype.closePath = vgcanvas.closePath;
VGContext.prototype.lineTo = vgcanvas.lineTo;
VGContext.prototype.moveTo = vgcanvas.moveTo;
VGContext.prototype.fill = vgcanvas.fill;
VGContext.prototype.stroke = vgcanvas.stroke;

VGContext.prototype.quadraticCurveTo = vgcanvas.quadraticCurveTo;
VGContext.prototype.bezierCurveTo = vgcanvas.bezierCurveTo;
VGContext.prototype.arc = vgcanvas.arc;
VGContext.prototype.rect = vgcanvas.rect;

VGContext.prototype.getScreenWidth = vgcanvas.getScreenWidth;
VGContext.prototype.getScreenHeight = vgcanvas.getScreenHeight;

VGContext.prototype.clip = vgcanvas.clip;
VGContext.prototype.save = vgcanvas.save;
VGContext.prototype.restore = vgcanvas.restore;

VGContext.prototype.swapBuffers = vgcanvas.swapBuffers;

module.exports.getContext = function(type) {
	switch(type) {
		case '2d':
		return new VGContext();
		default:
		return null;
	}
}
