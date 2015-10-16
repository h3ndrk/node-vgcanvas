# Insights

* `fillText`
    * renders nothing if no fonts are loaded (notice log output)
    * calculates off-screen how long the text is to use `textAlign` and `textBaseline` (loop involved) (performance warning)
    * saves the *path*-matrix and restores it at the end of drawing
        * translates to the start position
    * for rendering every character the *fill-paint*-matrix is saved and restored (to achieve correct gradient rendering) (performance warning)
    * kerning involves extra matrix translations for every character rendering
    * see also: *Text Kerning*
    * Conclusion:
        * may be slow because of many matrix operations and the extra loop
* `strokeText`
    * renders nothing if no fonts are loaded (notice log output)
    * calculates off-screen how long the text is to use `textAlign` and `textBaseline` (loop involved) (performance warning)
    * stores and restores e.g. *lineDash*-data
        * complex *lineDash*-data can result in bad performance (performance warning)
        * if the storing fails the text rendering fails which results in no text rendering
    * saves the *path*-matrix and restores it at the end of drawing
        * translates to the start position
    * for rendering every character the *fill-paint*-matrix is saved and restored (to achieve correct gradient rendering) (performance warning)
    * kerning involves extra matrix translations for every character rendering
    * see also: *Text Kerning*
    * Conclusion:
        * may be slow because of many matrix operations, the extra loop and extra loop for *lineDash*-data
* Text Kerning
    * enabled by default
    * can be en-/disabled by `ctx.kerning = <boolean>;`
    * some fonts do not support font kerning which results in disabled font kerning when rendering (does not reset `ctx.kerning`) (notice log output)
* Font Loading
    * uses *Freetype*
    * character size is `64 * 64 * 64 = 262144` (*Freetype* font units)
    * all coordinates are divided by the character size which results in lengths of `1`
    * counting of all characters of the font (loop involved) (performance warning)
    * for every character
        * character outline will be converted to a path (for use in OpenVG)
        * several sizes are computed for the character
    * the font is checked for availability for kerning support
    * fonts must not explicitly removed/clean-upped, they will automatically destroyed if the library exits
