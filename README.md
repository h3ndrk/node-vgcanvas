# node-vgcanvas

*Node.js* wrapper for *Canvas 2D API* targeting the *Raspberry Pi*. This wrapper uses *OpenVG* for performant GPU rendering.

The intention of this library is that every web developer can put *Javascript* code directly to the *Raspberry Pi*. This means that the library tries to be mostly conform to the *Canvas 2D API*. In addition the code will be executed on the powerful GPU of the *Raspberry Pi*.

* [W3C: HTML Canvas 2D Context](http://www.w3.org/TR/2015/PR-2dcontext-20150924/)
* [MDN: CanvasRenderingContext2D](https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D)

## Developer information

This section informs all developers about which features the *node-vgcanvas*-library has and which are not standard compliant to the *Canvas 2D API*. Everything not mentioned in this section should work as you expect the *Canvas 2D API* works.

### Coordinates

The coordinate system is the same which the *Canvas 2D API* uses. The upper left corner is the origin. In the right direction the x axis is positive, in the down direction the y axis is positive.

### Text Rendering

* without any loaded font nothing (text) will be rendered **(see log output)**
* the correct rendering position is calculated via `textAlign` and `textBaseline` (loop involved)
* intensive matrix-saving, -restoring and -modifying **(performance warning)**
    * *path*-matrix
        * saving and restoring for every text element
        * modifying for every character (kerning needs extra matrix modifications)
    * *paint*-matrix (to achieve correct gradient rendering)
        * saving and restoring for every character
        * modifying for every character
* stroked text anomalies
    * settings which are sensitive for scaling are scaled properly (includes `lineDash`-data which uses a loop: complex `lineDash`-data can result in bad performance) **(performance warning)**
* see also: *Text Kerning*

### Text Kerning

* enabled by default
* can be en-/disabled by `ctx.kerning = <boolean>;`
* some fonts do not support font kerning which results in disabled font kerning when rendering (does not reset `ctx.kerning`) **(see log output)**

### Font Loading

* uses *Freetype*
* character size is `64 * 64 * 64 = 262144` (*Freetype* font units)
* all coordinates are divided by the character size which results in lengths of `1`
* counting of all characters of the font (loop involved) **(performance warning)**
* for every character
    * character outline will be converted to a path (for use in OpenVG)
    * several sizes are computed for the character
* the font is checked for availability for kerning support
* fonts must not explicitly removed/clean-upped, they will automatically destroyed if the library exits

### Text Baseline

* `hanging`- and `ideographic` baselines differ from the standard *Canvas 2D API* (*Freetype* does not support these special baselines)
    * `hanging`: in the library the baseline sits on top of the highest character of the font
    * `ideographic`: in the library the baseline lays below the smallest character of the font

### Saving and Restoring

Be careful when saving and restoring multiple times in a single frame **(Performance warning)**. The following data will be stored:

* Several current matrices.
* Clipping region. Complex clipping regions (complex paths) may influence the performance.
* `lineDash`-data
* Fill- and Stroke-Colors.
* Current font. This involves some loops to store the correct font and to restore the correct font.

### Images

* uses *FreeImage*
* Many formats are suported: [FreeImage features](http://freeimage.sourceforge.net/features.html)
* `Image` is like `HTMLImageElement`, supported attributes are `src`, `onload`, `onerror`
* `ImageData.data` can be modified, but `ImageData.update` must be called manually since the actual data is stored in VRAM.
* `canvas.toBlob` does not create a `Blob` as specified in the *Canvas 2D API*, but a Node buffer.
* Currently, `ctx.drawImage` only supports `Image` as image source. This may change in future.

### Unsupported properties and methods

The following properties and methods are not implemented and will not be implemented in the future. Mostly that are experimental features.

* Transformation matrices are write-only in *node-vgcanvas*. It is not possible to read the current transformation matrix via `ctx.currentTransform`. This may change in the future.
* Text direction are not supported via `ctx.direction`.
* Filters are not supported via `ctx.filter`.
* Shadows are not supported via `ctx.shadowBlur`, `ctx.shadowColor`, `ctx.shadowOffsetX`, `ctx.shadowOffsetY`. Shadows are very ressource intense drawing operations and result in very bad performance.
* Hit Regions are not supported via `ctx.addHitRegion()`, `ctx.clearHitRegion()` and `ctx.removeHitRegion()`. Hit Regions cannot be implemented currently because all path data is in the VRAM which means that it is not accessable from the library.
* Focus Drawing is not supported via `ctx.drawFocusIfNeeded()`. There are no focus algorithms available by the library. This feature may be implemented by the application.
* Test-Point-In-Structure is not supported via `ctx.isPointInPath()` and `ctx.isPointInPath()`. Test-Point-In-Structure cannot be implemented currently because all path data is in the VRAM which means that it is not accessable from the library.
* Path Scrolling is not supported via `ctx.scrollPathIntoView()`.

See [STATUS.md](./STATUS.md) for more details of the currently supported properties and methods.

## Need help?

Contact the developers if you have questions: [dev.nipe.systems@gmail.com](mailto:dev.nipe.systems@gmail.com), [gebatzens@archlinux.info](gebatzens@archlinux.info)

## Found a bug?

Write an issue: [https://github.com/NIPE-SYSTEMS/node-vgcanvas/issues](https://github.com/NIPE-SYSTEMS/node-vgcanvas/issues)

## License

lastest GPL-license (see `LICENSE`-file)

Copyright (C) 2015 NIPE-SYSTEMS ([http://nipe-systems.de](http://nipe-systems.de)), Hauke Oldsen ([https://gebatzens.de](https://gebatzens.de))

### License of example font

The font ("Lato Regular") used by the examples is published under the OFL-license (see [OFL.txt](OFL.txt)).

Further informations can be found at: [https://www.google.com/fonts/specimen/Lato](https://www.google.com/fonts/specimen/Lato)
