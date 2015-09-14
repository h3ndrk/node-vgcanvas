var vgcanvas = require('../build/Release/vgcanvas');
var color = require('onecolor');

var VGContext = function() {
  var self = this;

  vgcanvas.init();

  self.fillStyleValue = 'black';

  Object.defineProperty(this, "fillStyle", {
    set: function(value) {
      self.setFillStyle(color(value));
      self.fillStyleValue = value;
    },
    get: function() {
      return self.fillStyleValue;
    }
  });
};

VGContext.prototype.setFillStyle = function(color) {
  vgcanvas.setFillStyle(color.red(), color.green(), color.blue(), color.alpha());
}

VGContext.prototype.fillRect = vgcanvas.fillRect;
VGContext.prototype.clearRect = vgcanvas.clearRect;

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
