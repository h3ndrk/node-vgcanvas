# Insights

* Text Rendering
    * without any loaded font nothing (text) will be rendered
    * the correct rendering position is calculated via `textAlign` and `textBaseline` (loop involved)
    * intensive matrix-saving, -restoring and -modifying (performance warning)
        * *path*-matrix
            * saving and restoring for every text element
            * modifying for every character (kerning needs extra matrix modifications)
        * *paint*-matrix (to achieve correct gradient rendering)
            * saving and restoring for every character
            * modifying for every character
    * stroked text anomalies
        * settings which are sensitive for scaling are scaled properly (includes `lineDash`-data which uses a loop: complex `lineDash`-data can result in bad performance) (performance warning)
    * see also: *Text Kerning*
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
* `textBaseline`
    * `hanging`- and `ideographic` baselines differ from the standard *Canvas 2D API* (*Freetype* does not support these special baselines)
        * `hanging`: the baseline sits on top of the highest character of the font
        * `ideographic`: the baseline lays below the smallest character of the font

If you have questions contact the developer: [dev.nipe.systems@gmail.com](mailto:dev.nipe.systems@gmail.com)

Found a bug? https://github.com/NIPE-SYSTEMS/node-vgcanvas/issues
