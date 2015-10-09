var color_names = {
	black: [ 0, 0, 0, 255 ],
	silver: [ 192, 192, 192, 255 ],
	gray: [ 128, 128, 128, 255 ],
	white: [ 255, 255, 255, 255 ],
	maroon: [ 128, 0, 0, 255 ],
	red: [ 255, 0, 0, 255 ],
	purple: [ 128, 0, 128, 255 ],
	fuchsia: [ 255, 0, 255, 255 ],
	green: [ 0, 128, 0, 255 ],
	lime: [ 0, 255, 0, 255 ],
	olive: [ 128, 128, 0, 255 ],
	yellow: [ 255, 255, 0, 255 ],
	navy: [ 0, 0, 128, 255 ],
	blue: [ 0, 0, 255, 255 ],
	teal: [ 0, 128, 128, 255 ],
	aqua: [ 0, 255, 255, 255 ],
	orange: [ 255, 165, 0, 255 ],
	aliceblue: [ 240, 248, 255, 255 ],
	antiquewhite: [ 250, 235, 215, 255 ],
	aquamarine: [ 127, 255, 212, 255 ],
	azure: [ 240, 255, 255, 255 ],
	beige: [ 245, 245, 220, 255 ],
	bisque: [ 255, 228, 196, 255 ],
	blanchedalmond: [ 255, 228, 196, 255 ],
	blueviolet: [ 138, 43, 226, 255 ],
	brown: [ 165, 42, 42, 255 ],
	burlywood: [ 222, 184, 135, 255 ],
	cadetblue: [ 95, 158, 160, 255 ],
	chartreuse: [ 127, 255, 0, 255 ],
	chocolate: [ 210, 105, 30, 255 ],
	coral: [ 255, 127, 80, 255 ],
	cornflowerblue: [ 100, 149, 237, 255 ],
	cornsilk: [ 255, 248, 220, 255 ],
	crimson: [ 220, 20, 60, 255 ],
	darkblue: [ 0, 0, 139, 255 ],
	darkcyan: [ 0, 139, 139, 255 ],
	darkgoldenrod: [ 184, 134, 11, 255 ],
	darkgray: [ 169, 169, 169, 255 ],
	darkgreen: [ 0, 100, 0, 255 ],
	darkgrey: [ 169, 169, 169, 255 ],
	darkkhaki: [ 189, 183, 107, 255 ],
	darkmagenta: [ 139, 0, 139, 255 ],
	darkolivegreen: [ 85, 107, 47, 255 ],
	darkorange: [ 255, 140, 0, 255 ],
	darkorchid: [ 153, 50, 204, 255 ],
	darkred: [ 139, 0, 0, 255 ],
	darksalmon: [ 233, 150, 122, 255 ],
	darkseagreen: [ 143, 188, 143, 255 ],
	darkslateblue: [ 72, 61, 139, 255 ],
	darkslategray: [ 47, 79, 79, 255 ],
	darkslategrey: [ 47, 79, 79, 255 ],
	darkturquoise: [ 0, 206, 209, 255 ],
	darkviolet: [ 148, 0, 211, 255 ],
	deeppink: [ 255, 20, 147, 255 ],
	deepskyblue: [ 0, 191, 255, 255 ],
	dimgray: [ 105, 105, 105, 255 ],
	dimgrey: [ 105, 105, 105, 255 ],
	dodgerblue: [ 30, 144, 255, 255 ],
	firebrick: [ 178, 34, 34, 255 ],
	floralwhite: [ 255, 250, 240, 255 ],
	forestgreen: [ 34, 139, 34, 255 ],
	gainsboro: [ 220, 220, 220, 255 ],
	ghostwhite: [ 248, 248, 255, 255 ],
	gold: [ 255, 215, 0, 255 ],
	goldenrod: [ 218, 165, 32, 255 ],
	greenyellow: [ 173, 255, 47, 255 ],
	grey: [ 128, 128, 128, 255 ],
	honeydew: [ 240, 255, 240, 255 ],
	hotpink: [ 255, 105, 180, 255 ],
	indianred: [ 205, 92, 92, 255 ],
	indigo: [ 75, 0, 130, 255 ],
	ivory: [ 255, 255, 240, 255 ],
	khaki: [ 240, 230, 140, 255 ],
	lavender: [ 230, 230, 250, 255 ],
	lavenderblush: [ 255, 240, 245, 255 ],
	lawngreen: [ 124, 252, 0, 255 ],
	lemonchiffon: [ 255, 250, 205, 255 ],
	lightblue: [ 173, 216, 230, 255 ],
	lightcoral: [ 240, 128, 128, 255 ],
	lightcyan: [ 224, 255, 255, 255 ],
	lightgoldenrodyellow: [ 250, 250, 210, 255 ],
	lightgray: [ 211, 211, 211, 255 ],
	lightgreen: [ 144, 238, 144, 255 ],
	lightgrey: [ 211, 211, 211, 255 ],
	lightpink: [ 255, 182, 193, 255 ],
	lightsalmon: [ 255, 160, 122, 255 ],
	lightseagreen: [ 32, 178, 170, 255 ],
	lightskyblue: [ 135, 206, 250, 255 ],
	lightslategray: [ 119, 136, 153, 255 ],
	lightslategrey: [ 119, 136, 153, 255 ],
	lightsteelblue: [ 176, 196, 222, 255 ],
	lightyellow: [ 255, 255, 224, 255 ],
	limegreen: [ 50, 205, 50, 255 ],
	linen: [ 250, 240, 230, 255 ],
	mediumaquamarine: [ 102, 205, 170, 255 ],
	mediumblue: [ 0, 0, 205, 255 ],
	mediumorchid: [ 186, 85, 211, 255 ],
	mediumpurple: [ 147, 112, 219, 255 ],
	mediumseagreen: [ 60, 179, 113, 255 ],
	mediumslateblue: [ 123, 104, 238, 255 ],
	mediumspringgreen: [ 0, 250, 154, 255 ],
	mediumturquoise: [ 72, 209, 204, 255 ],
	mediumvioletred: [ 199, 21, 133, 255 ],
	midnightblue: [ 25, 25, 112, 255 ],
	mintcream: [ 245, 255, 250, 255 ],
	mistyrose: [ 255, 228, 225, 255 ],
	moccasin: [ 255, 228, 181, 255 ],
	navajowhite: [ 255, 222, 173, 255 ],
	oldlace: [ 253, 245, 230, 255 ],
	olivedrab: [ 107, 142, 35, 255 ],
	orangered: [ 255, 69, 0, 255 ],
	orchid: [ 218, 112, 214, 255 ],
	palegoldenrod: [ 238, 232, 170, 255 ],
	palegreen: [ 152, 251, 152, 255 ],
	paleturquoise: [ 175, 238, 238, 255 ],
	palevioletred: [ 219, 112, 147, 255 ],
	papayawhip: [ 255, 239, 213, 255 ],
	peachpuff: [ 255, 218, 185, 255 ],
	peru: [ 205, 133, 63, 255 ],
	pink: [ 255, 192, 203, 255 ],
	plum: [ 221, 160, 221, 255 ],
	powderblue: [ 176, 224, 230, 255 ],
	rosybrown: [ 188, 143, 143, 255 ],
	royalblue: [ 65, 105, 225, 255 ],
	saddlebrown: [ 139, 69, 19, 255 ],
	salmon: [ 250, 128, 114, 255 ],
	sandybrown: [ 244, 164, 96, 255 ],
	seagreen: [ 46, 139, 87, 255 ],
	seashell: [ 255, 245, 238, 255 ],
	sienna: [ 160, 82, 45, 255 ],
	skyblue: [ 135, 206, 235, 255 ],
	slateblue: [ 106, 90, 205, 255 ],
	slategray: [ 112, 128, 144, 255 ],
	slategrey: [ 112, 128, 144, 255 ],
	snow: [ 255, 250, 250, 255 ],
	springgreen: [ 0, 255, 127, 255 ],
	steelblue: [ 70, 130, 180, 255 ],
	tan: [ 210, 180, 140, 255 ],
	thistle: [ 216, 191, 216, 255 ],
	tomato: [ 255, 99, 71, 255 ],
	turquoise: [ 64, 224, 208, 255 ],
	violet: [ 238, 130, 238, 255 ],
	wheat: [ 245, 222, 179, 255 ],
	whitesmoke: [ 245, 245, 245, 255 ],
	yellowgreen: [ 154, 205, 50, 255 ],
	rebeccapurple: [ 102, 51, 153, 255 ]
};

/**
 * This function converts colors from HSL color space to the RGB color space.
 * This function is only used internally.
 * @param h The hue of the HSL color. The value must be between 0 and 1.
 * @param s The saturation of the HSL color. The value must be between 0 and 1.
 * @param l The lightness of the HSL color. The value must be between 0 and 1.
 * @return An array of three values which represent the red, green and blue
 *         color component (in this order) of the RGB color. The values are
 *         between 0 and 255.
 */
function hslToRgb(h, s, l)
{
	var r, g, b;
	
	if(s == 0)
	{
		r = g = b = l; // achromatic
	}
	else
	{
		var hue2rgb = function hue2rgb(p, q, t)
		{
			if(t < 0)
			{
				t += 1;
			}
			
			if(t > 1)
			{
				t -= 1;
			}
			
			if(t < 1 / 6)
			{
				return p + (q - p) * 6 * t;
			}
			
			if(t < 1 / 2)
			{
				return q;
			}
			
			if(t < 2 / 3)
			{
				return p + (q - p) * (2 / 3 - t) * 6;
			}
			
			return p;
		}
		
		var q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		var p = 2 * l - q;
		r = hue2rgb(p, q, h + 1/3);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1/3);
	}
	
	return [
		r * 255,
		g * 255,
		b * 255
	];
}

/**
 * This function decodes an color string which represents a standard CSS color
 * value. See http://www.w3.org/TR/css3-color/ for more informations.
 * @param colorString The color string which should be decoded.
 * @return An array of four values. The first three values represent the RGB
 *         color component (red, green, blue, in this order). The last value
 *         represents the alpha component of the color. The returned values
 *         are between 0 and 255. If the value is not a valid CSS color string
 *         or the color name does not exist the function returns null.
 */
module.exports.decode = function(colorString)
{
	var match = null;
	
	// test for hex (3 digits)
	match = /^#([0-9a-f])([0-9a-f])([0-9a-f])$/ig.exec(colorString);
	if(match != null)
	{
		return [
			parseInt(match[1], 16) * 0x11 / 0xff,
			parseInt(match[2], 16) * 0x11 / 0xff,
			parseInt(match[3], 16) * 0x11 / 0xff,
			1
		];
	}
	
	// test for hex (6 digits)
	match = /^#([0-9a-f]{2})([0-9a-f]{2})([0-9a-f]{2})$/ig.exec(colorString);
	if(match != null)
	{
		return [
			parseInt(match[1], 16) / 0xff,
			parseInt(match[2], 16) / 0xff,
			parseInt(match[3], 16) / 0xff,
			1
		];
	}
	
	// test for rgb()
	match = /^rgb\s*\(\s*(\d+\s*%?)\s*,\s*(\d+\s*%?)\s*,\s*(\d+\s*%?)\s*\)/ig.exec(colorString);
	if(match != null)
	{
		var color_red = match[1];
		var color_green = match[2];
		var color_blue = match[3];
		
		if(color_red.charAt(color_red.length - 1) == "%")
		{
			color_red = parseInt(color_red.replace(/%*/g, "").trim()) / 100;
		}
		else
		{
			color_red = parseInt(color_red) / 0xff;
		}
		
		if(color_green.charAt(color_green.length - 1) == "%")
		{
			color_green = parseInt(color_green.replace(/%*/g, "").trim()) / 100;
		}
		else
		{
			color_green = parseInt(color_green) / 0xff;
		}
		
		if(color_blue.charAt(color_blue.length - 1) == "%")
		{
			color_blue = parseInt(color_blue.replace(/%*/g, "").trim()) / 100;
		}
		else
		{
			color_blue = parseInt(color_blue) / 0xff;
		}
		
		return [
			color_red,
			color_green,
			color_blue,
			1
		];
	}
	
	// test for rgba()
	match = /^rgba\s*\(\s*(\d+\s*%?)\s*,\s*(\d+\s*%?)\s*,\s*(\d+\s*%?)\s*,\s*(\.?\d+)\s*\)/ig.exec(colorString);
	if(match != null)
	{
		var color_red = match[1];
		var color_green = match[2];
		var color_blue = match[3];
		var color_alpha = match[4];
		
		if(color_red.charAt(color_red.length - 1) == "%")
		{
			color_red = parseInt(color_red.replace(/%*/g, "").trim()) / 100;
		}
		else
		{
			color_red = parseInt(color_red) / 0xff;
		}
		
		if(color_green.charAt(color_green.length - 1) == "%")
		{
			color_green = parseInt(color_green.replace(/%*/g, "").trim()) / 100;
		}
		else
		{
			color_green = parseInt(color_green) / 0xff;
		}
		
		if(color_blue.charAt(color_blue.length - 1) == "%")
		{
			color_blue = parseInt(color_blue.replace(/%*/g, "").trim()) / 100;
		}
		else
		{
			color_blue = parseInt(color_blue) / 0xff;
		}
		
		color_alpha = parseFloat(color_alpha);
		
		return [
			color_red,
			color_green,
			color_blue,
			color_alpha
		];
	}
	
	// test for hsl()
	match = /^hsl\s*\(\s*(\d+)\s*,\s*(\d+\s*%)\s*,\s*(\.?\d+\s*%)\s*\)/ig.exec(colorString);
	if(match != null)
	{
		var color_hue = match[1];
		var color_saturation = match[2];
		var color_lightness = match[3];
		var color_rgb = [ 0, 0, 0 ];
		
		color_hue = parseInt(color_hue) / 360;
		color_saturation = parseInt(color_saturation.replace(/%*/g, "").trim()) / 100;
		color_lightness = parseInt(color_lightness.replace(/%*/g, "").trim()) / 100;
		
		color_rgb = hslToRgb(color_hue, color_saturation, color_lightness);
		
		return [
			color_rgb[0] / 0xff,
			color_rgb[1] / 0xff,
			color_rgb[2] / 0xff,
			1
		];
	}
	
	// test for hsla()
	match = /^hsla\s*\(\s*(\d+)\s*,\s*(\d+\s*%)\s*,\s*(\d+\s*%)\s*,\s*(\d+)\s*\)/ig.exec(colorString);
	if(match != null)
	{
		var color_hue = match[1];
		var color_saturation = match[2];
		var color_lightness = match[3];
		var color_alpha = match[4];
		var color_rgb = [ 0, 0, 0 ];
		
		color_hue = parseInt(color_hue) / 360;
		color_saturation = parseInt(color_saturation.replace(/%*/g, "").trim()) / 100;
		color_lightness = parseInt(color_lightness.replace(/%*/g, "").trim()) / 100;
		color_alpha = parseFloat(color_alpha);
		
		color_rgb = hslToRgb(color_hue, color_saturation, color_lightness);
		
		return [
			color_rgb[0] / 0xff,
			color_rgb[1] / 0xff,
			color_rgb[2] / 0xff,
			color_alpha
		];
	}
	
	// test for named color
	match = color_names[colorString.trim()]
	if(match != null)
	{
		return match;
	}
	
	return null;
}

/**
 * This function encodes four color components (red, green blue and alpha
 * component) to a valid CSS color string.
 * @param red The red component of the RGB color. The value must be between 0
 *            and 255.
 * @param green The green component of the RGB color. The value must be between
 *            0 and 255.
 * @param blue The blue component of the RGB color. The value must be between 0
 *             and 255.
 * @param alpha The alpha component of the RGB color. The value must be between
 *              0 and 255.
 * @return A valid CSS color string. If the given color components are not valid
 *         or out of range the function returns a black color.
 */
module.exports.encode = function(red, green, blue, alpha)
{
	// https://stackoverflow.com/questions/11068240/what-is-the-most-efficient-way-to-parse-a-css-color-in-javascript
	// An up-to-date browser will convert any given colour to rgb() format in
	// its computed style. Just get it back, and read it out.
	
	// test for invalid color value types
	if(typeof red != "number" || typeof green != "number" || typeof blue != "number" || typeof alpha != "number")
	{
		return "rgb(0, 0, 0)";
	}
	
	// test for color values out of range
	if(red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0 || alpha > 255 || alpha < 0)
	{
		return "rgb(0, 0, 0)";
	}
	
	if(alpha != 255)
	{
		return "rgba(" + red + ", " + green + ", " + blue + ", " + (alpha / 255) + ")";
	}
	else
	{
		return "rgb(" + red + ", " + green + ", " + blue + ")";
	}
}
