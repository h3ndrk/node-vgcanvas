var canvas = require('../lib/canvas')

var ctx = canvas.getContext('2d');

ctx.fillStyle = 'red';

var x = 0;

setInterval(function() {
  ctx.clearRect(0, 0, ctx.getScreenWidth(), ctx.getScreenHeight());
  ctx.fillRect(x, 100, 100, 100);
  x++;

  ctx.swapBuffers();
}, 50);
