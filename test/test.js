var canvas = require('../lib/canvas')

var ctx = canvas.getContext('2d');

var x = 0;
var y2 = 0;

setInterval(function() {
  x++;
  y2 = Math.sin(x * 0.1) * 50;

  ctx.clearRect(0, 0, ctx.getScreenWidth(), ctx.getScreenHeight());

  ctx.fillStyle = '#fff';
  ctx.fillRect(x, 100, 100, 100);

  ctx.fillStyle = '#865656';
  ctx.fillRect(400, y2 + 400, 100, 100);

  ctx.fillStyle = 'gold';
  ctx.fillRect(550, y2 * 0.5 + 400, 100, 100);

  ctx.swapBuffers();
}, 20);
