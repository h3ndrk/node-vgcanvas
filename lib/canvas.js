var vgcanvas = require('../build/Release/vgcanvas');
var color = require('onecolor');

var VGContext = function() {
	var self = this;

	vgcanvas.init();

	self.fillStyleValue = 'black';
	self.strokeStyleValue = 'black';
	self.lineWidthValue = 1.0;
	self.lineCapValue = 'butt';
	self.lineJoinValue = 'miter';

	Object.defineProperty(this, "fillStyle", {
		set: function(value) {
			self.setFillStyle(color(value));
			self.fillStyleValue = value;
		},
		get: function() {
			return self.fillStyleValue;
		}
	});

	Object.defineProperty(this, "strokeStyle", {
		set: function(value) {
			self.setStrokeStyle(color(value));
			self.strokeStyleValue = value;
		},
		get: function() {
			return self.strokeStyleValue;
		}
	});

	Object.defineProperty(this, "lineWidth", {
		set: function(value) {
			self.setLineWidth(value);
			self.lineWidthValue = value;
		},
		get: function() {
			return self.lineWidthValue;
		}
	});

	Object.defineProperty(this, "lineCap", {
		set: function(value) {
			self.setLineCap(value);
			self.lineCapValue = value;
		},
		get: function() {
			return self.lineCapValue;
		}
	});

	Object.defineProperty(this, "lineJoin", {
		set: function(value) {
			self.setLineJoin(value);
			self.lineJoinValue = value;
		},
		get: function() {
			return self.lineJoinValue;
		}
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

VGContext.prototype.getScreenWidth = vgcanvas.getScreenWidth;
VGContext.prototype.getScreenHeight = vgcanvas.getScreenHeight;

VGContext.prototype.swapBuffers = vgcanvas.swapBuffers;

module.exports.getContext = function(type) {
	switch(type) {
		case '2d':
		return new VGContext();
		default:
		return null;
	}
}
