var vgcanvas = require('../build/Release/vgcanvas');
var color = require('./color').decode;

var states = [];

var VGContext = function() {
	var self = this;

	vgcanvas.init();

	function cleanup() {
		vgcanvas.cleanup();
		//gc();
		process.exit(0);
	}

	process.on('SIGTERM', cleanup);
	process.on('SIGINT', cleanup);

	self.fillStyleValue = '#000';
	self.strokeStyleValue = '#000';

	Object.defineProperty(this, "fillStyle", {
		set: function(value) {
			self.setStyle(false, value);
			self.fillStyleValue = value;
		},
		get: function() {
			return self.fillStyleValue;
		}
	});

	Object.defineProperty(this, "strokeStyle", {
		set: function(value) {
			self.setStyle(true, value);
			self.strokeStyleValue = value;
		},
		get: function() {
			return self.strokeStyleValue;
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

	Object.defineProperty(this, "font", {
		set: function(font) {
			var parts = font.split(' ');
			var size = parseInt(parts[0].substring(0, parts[0].length - 2));

			vgcanvas.setFont(size, font.substring(parts[0].length + 1));
		},
		get: function() {
			return 'todo';
		}
	});
};

vgcanvas.Gradient.prototype.addColorStop = function(pos, c) {
	c = color(c);
	this.addColorStopRGBA(pos, c[0], c[1], c[2], c[3]);
};

VGContext.prototype.createLinearGradient = function(x1, y1, x2, y2) {
	return new vgcanvas.Gradient('linear', x1, y1, x2, y2);
};

VGContext.prototype.createRadialGradient = function(cx, cy, r, fx, fy, fr) {
	return new vgcanvas.Gradient('radial', cx, cy, r, fx, fy);
};

VGContext.prototype.setStyle = function(type, obj) {
	if(typeof obj === 'string' || obj instanceof String) {
		obj = color(obj);
		vgcanvas.setStyle(type, [obj[0], obj[1], obj[2], obj[3]]);
	} else {
		vgcanvas.setStyle(type, obj);
	}
};

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

VGContext.prototype.loadFont = vgcanvas.loadFont;
VGContext.prototype.setFont = vgcanvas.setFont;
VGContext.prototype.fillText = vgcanvas.fillText;
VGContext.prototype.strokeText = vgcanvas.strokeText;

VGContext.prototype.getScreenWidth = vgcanvas.getScreenWidth;
VGContext.prototype.getScreenHeight = vgcanvas.getScreenHeight;

VGContext.prototype.clip = vgcanvas.clip;
VGContext.prototype.save = function() {
	states.push({ stroke: this.strokeStyleValue, fill: this.fillStyleValue });
	return vgcanvas.save();
}
VGContext.prototype.restore = function() {
	if(states.length == 0) {
		throw new TypeError("states.length is 0");
	}
	var state = states.pop();
	this.strokeStyleValue = state.stroke;
	this.fillStyleValue = state.fill;

	return vgcanvas.restore();
};

VGContext.prototype.swapBuffers = vgcanvas.swapBuffers;
VGContext.prototype.cleanup = vgcanvas.cleanup;

module.exports.getContext = function(type) {
	switch(type) {
		case '2d':
			return new VGContext();
		default:
			return null;
	}
}
