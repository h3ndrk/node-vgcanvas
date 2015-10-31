var vgcanvas = require("../lib/canvas");

var canvas = null;
var ctx = null;
var animationAmount = 7;
var animationId = 0;
var animationElapsed = 0;
var animationLast = null;
var animationDelta = 0;
var animationRequest = null;
var animationRandomValue = null;
var animationSubtitleElapsed = 0;
var animationSubtitleState = true;
var animationTextWidth = 0;
var animationTextHeight = 0;
var animationTextHeightAscent = 0;

function smoothstep(value)
{
	return value * value * value * (value * (value * 6 - 15) + 10)
}

var start = function()
{
	canvas = new vgcanvas.Canvas();
	if(canvas != null)
	{
		ctx = canvas.getContext("2d");
	}
	
	if(ctx != null)
	{
		ctx.loadFont("./test/Lato-Regular.ttf", "Lato");
		
		animationId = 0;
		animationElapsed = 0;
		
		ctx.fillStyle = "#FFFFFF";
		ctx.strokeStyle = "#FFFFFF";
		ctx.font = "100px Lato";
		ctx.textAlign = "center";
		ctx.textBaseline = "middle";
		ctx.lineWidth = 2;
		
		var metrics = ctx.measureText("node-vgcanvas");
		animationTextWidth = metrics.width;
		animationTextHeight = metrics.actualBoundingBoxAscent + metrics.actualBoundingBoxDescent;
		animationTextHeightAscent = metrics.actualBoundingBoxAscent;
		
		canvas.requestAnimationFrame(paint);
	}
};

function changeAnimation()
{
	animationId = Math.round(Math.random() * (animationAmount - 1));
	animationElapsed = 0;
	animationRandomValue = null;
}

function stopAnimation()
{
	if(animationRequest != null)
	{
		//cancelAnimationFrame(animationRequest);
		animationRequest = null;
	}
}

function paint(timestamp)
{
	if(animationLast == null)
	{
		animationLast = timestamp;
	}
	
	animationDelta = timestamp - animationLast;
	
	if(animationRandomValue == null)
	{
		animationRandomValue = Math.random();
	}
	
	ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
	
	switch(animationId)
	{
		case 0:
		{
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2, ctx.canvas.height / 2);
			
			if(animationElapsed >= Math.random() * 100 + 300)
			{
				changeAnimation();
			}
			
			break;
		}
		case 1:
		{
			ctx.save();
			ctx.beginPath();
			ctx.rect(0, 0, ctx.canvas.width, ctx.canvas.height / 2 + 10 + animationRandomValue * 50);
			ctx.clip();
			ctx.globalAlpha = Math.random() * 0.75;
			ctx.fillStyle = "#00F9FF";
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2 - 7, ctx.canvas.height / 2);
			ctx.globalAlpha = Math.random() * 0.75;
			ctx.fillStyle = "#7DFF52";
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2 - 2, ctx.canvas.height / 2 + 2);
			ctx.globalAlpha = Math.random() * 0.75;
			ctx.fillStyle = "#FF4747";
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2 + 3, ctx.canvas.height / 2);
			ctx.restore();
			ctx.globalAlpha = 1;
			ctx.fillStyle = "#FFFFFF";
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2 - 2, ctx.canvas.height / 2);
			
			if(animationElapsed >= Math.random() * 100 + 100)
			{
				changeAnimation();
			}
			
			break;
		}
		case 2:
		{
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2, ctx.canvas.height / 2);
			ctx.fillRect(ctx.canvas.width / 2 - (Math.random() * 20), ctx.canvas.height / 2 + 10 + Math.random() * 20, 500 + Math.random() * 100, 6);
			ctx.fillRect(ctx.canvas.width / 2 + (Math.random() * 20), ctx.canvas.height / 2 + Math.random() * 20, 400 + Math.random() * 100, 2);
			ctx.fillStyle = "#000000";
			ctx.fillRect(ctx.canvas.width / 2 + (Math.random() * 20 - 100), ctx.canvas.height / 2 - 10 + Math.random() * 20, 500 + Math.random() * 100, 10);
			ctx.fillStyle = "#FFFFFF";
			
			if(animationElapsed >= Math.random() * 100 + 100)
			{
				changeAnimation();
			}
			
			break;
		}
		case 3:
		{
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2, ctx.canvas.height / 2);
			ctx.fillRect(ctx.canvas.width / 2 - (Math.random() * 20 + 450), ctx.canvas.height / 2 - 15 + Math.random() * 20, 250 + Math.random() * 100, 6);
			ctx.fillRect(ctx.canvas.width / 2 - (Math.random() * 20 + 450), ctx.canvas.height / 2 + Math.random() * 20, 300 + Math.random() * 100, 2);
			ctx.fillStyle = "#000000";
			ctx.fillRect(ctx.canvas.width / 2 - (Math.random() * 20 + 450), ctx.canvas.height / 2 + 20 + Math.random() * 20, 300 + Math.random() * 100, 10);
			ctx.fillStyle = "#FFFFFF";
			
			if(animationElapsed >= Math.random() * 100 + 100)
			{
				changeAnimation();
			}
			
			break;
		}
		case 4:
		{
			ctx.save();
			ctx.beginPath();
			ctx.rect(0, 0, ctx.canvas.width, ctx.canvas.height / 2 - 10 + animationRandomValue * 30);
			ctx.clip();
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2, ctx.canvas.height / 2);
			ctx.restore();
			ctx.save();
			ctx.beginPath();
			ctx.rect(0, ctx.canvas.height / 2 - 10 + animationRandomValue * 30, ctx.canvas.width, ctx.canvas.height);
			ctx.clip();
			ctx.fillText("node-vgcanvas", ctx.canvas.width / 2 + ((Math.random() >= 0.5)?(15):(-10)), ctx.canvas.height / 2);
			ctx.restore();
			
			if(animationElapsed >= Math.random() * 100 + 100)
			{
				changeAnimation();
			}
			
			break;
		}
		case 5:
		{
			ctx.strokeText("node-vgcanvas", ctx.canvas.width / 2, ctx.canvas.height / 2);
			ctx.strokeRect(ctx.canvas.width / 2 - animationTextWidth / 2, ctx.canvas.height / 2 - 36.8, animationTextWidth, animationTextHeight);
			
			if(animationElapsed >= Math.random() * 50 + 50)
			{
				changeAnimation();
			}
			
			break;
		}
		case 6:
		{
			ctx.strokeText("node-vgcanvas", ctx.canvas.width / 2, ctx.canvas.height / 2);
			
			if(animationElapsed >= Math.random() * 50 + 50)
			{
				changeAnimation();
			}
			
			break;
		}
	}
	
	ctx.globalAlpha = 0.5;
	ctx.font = "20px Lato";
	ctx.fillText("Hardware accelerated Canvas 2D API for the Raspberry Pi", ctx.canvas.width / 2, ctx.canvas.height / 2 + 250);
	ctx.globalAlpha = 1;
	ctx.save();
	ctx.beginPath();
	if(animationSubtitleState)
	{
		ctx.rect(smoothstep(animationSubtitleElapsed / 800) * 700 + ctx.canvas.width / 2 - 350, 0, ctx.canvas.width, ctx.canvas.height);
	}
	else
	{
		ctx.rect(0, 0, smoothstep(animationSubtitleElapsed / 800) * 700 + ctx.canvas.width / 2 - 350, ctx.canvas.height);
	}
	ctx.clip();
	ctx.fillText("Hardware accelerated Canvas 2D API for the Raspberry Pi", ctx.canvas.width / 2, ctx.canvas.height / 2 + 250);
	ctx.restore();
	ctx.font = "100px Lato";
	
	if(animationSubtitleElapsed >= 800)
	{
		animationSubtitleElapsed = 0;
		animationSubtitleState = !animationSubtitleState;
	}
	
	animationElapsed += animationDelta;
	animationSubtitleElapsed += animationDelta;
	animationLast = timestamp;
	
	animationRequest = canvas.requestAnimationFrame(paint);
}

start();
