# node-vgcanvas

Node.js wrapper for Canvas 2D API targeting the Raspberry Pi. This wrapper uses OpenVG for performant GPU rendering.

## Canvas 2D API implementation status

Canvas 2D Method | C implementation | C++ wrapper implementation | Node.JS implementation
-----------------|------------------|----------------------------|-----------------------
`VGContext.canvas` |   |   |   
`VGContext.currentTransform` |   |   |   
`VGContext.direction` |   |   |   
`VGContext.fillStyle` |   |   |   
`VGContext.filter` |   |   |   
`VGContext.font` |   |   |   
`VGContext.globalAlpha` | implemented |   |   
`VGContext.globalCompositeOperation` |   |   |   
`VGContext.imageSmoothingEnabled` |   |   |   
`VGContext.lineCap` | implemented |   |   
`VGContext.lineDashOffset` | implemented |   |   
`VGContext.lineJoin` | implemented |   |   
`VGContext.lineWidth` | implemented |   |   
`VGContext.miterLimit` |   |   |   
`VGContext.shadowBlur` |   |   |   
`VGContext.shadowColor` |   |   |   
`VGContext.shadowOffsetX` |   |   |   
`VGContext.shadowOffsetY` |   |   |   
`VGContext.strokeStyle` |   |   |   
`VGContext.textAlign` |   |   |   
`VGContext.textBaseline` |   |   |   
`VGContext.textBaseline` |   |   |   
`VGContext.addHitRegion()` |   |   |   
`VGContext.arc()` | implemented |   |   
`VGContext.arcTo()` |   |   |   
`VGContext.asyncDrawXULElement()` |   |   |   
`VGContext.beginPath()` | implemented |   |   
`VGContext.bezierCurveTo()` | implemented |   |   
`VGContext.clearHitRegion()` |   |   |   
`VGContext.clearRect()` | implemented |   |   
`VGContext.clip()` | partly implemented (`save` and `restore` missing) |   |   
`VGContext.closePath()` | implemented |   |   
`VGContext.createImageData()` |   |   |   
`VGContext.createLinearGradient()` |   |   |   
`VGContext.createPattern()` |   |   |   
`VGContext.createRadialGradient()` |   |   |   
`VGContext.drawFocusIfNeeded()` |   |   |   
`VGContext.drawImage()` |   |   |   
`VGContext.drawWindow()` |   |   |   
`VGContext.ellipse()` |   |   |   
`VGContext.fill()` |   |   |   
`VGContext.fillRect()` |   |   |   
`VGContext.fillText()` |   |   |   
`VGContext.getImageData()` |   |   |   
`VGContext.getLineDash()` |   |   |   
`VGContext.isPointInPath()` |   |   |   
`VGContext.isPointInStroke()` |   |   |   
`VGContext.lineTo()` | implemented |   |   
`VGContext.measureText()` |   |   |   
`VGContext.moveTo()` | implemented |   |   
`VGContext.putImageData()` |   |   |   
`VGContext.quadraticCurveTo()` | implemented |   |   
`VGContext.rect()` | implemented |   |   
`VGContext.removeHitRegion()` |   |   |   
`VGContext.resetTransform()` |   |   |   
`VGContext.restore()` | implemented |   |   
`VGContext.rotate()` |   |   |   
`VGContext.save()` | partly implemented (`restore` missing) |   |   
`VGContext.scrollPathIntoView()` |   |   |   
`VGContext.setLineDash()` | implemented |   |   
`VGContext.setTransform()` |   |   |   
`VGContext.stroke()` |   |   |   
`VGContext.strokeRect()` |   |   |   
`VGContext.strokeText()` |   |   |   
`VGContext.transform()` |   |   |   
`VGContext.translate()` |   |   |   
