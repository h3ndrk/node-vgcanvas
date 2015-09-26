# node-vgcanvas

Node.js wrapper for Canvas 2D API targeting the Raspberry Pi. This wrapper uses OpenVG for performant GPU rendering.

## Canvas 2D API implementation status

Canvas 2D Method | C implementation | C++ wrapper implementation | Node.JS implementation
-----------------|------------------|----------------------------|-----------------------
`VGContext.canvas` |   |   |   
`VGContext.currentTransform` |   |   |   
`VGContext.direction` |   |   |   
`VGContext.fillStyle` | API unfinished |   |   
`VGContext.filter` |   |   |   
`VGContext.font` | API unfinished |   |   
`VGContext.globalAlpha` | implemented |   |   
`VGContext.globalCompositeOperation` |   |   |   
`VGContext.imageSmoothingEnabled` |   |   |   
`VGContext.lineCap` | implemented |   |   
`VGContext.lineDashOffset` | implemented |   |   
`VGContext.lineJoin` | implemented |   |   
`VGContext.lineWidth` | implemented |   |   
`VGContext.miterLimit` | implemented |   |   
`VGContext.shadowBlur` |   |   |   
`VGContext.shadowColor` |   |   |   
`VGContext.shadowOffsetX` |   |   |   
`VGContext.shadowOffsetY` |   |   |   
`VGContext.strokeStyle` | API unfinished |   |   
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
`VGContext.clip()` | implemented |   |   
`VGContext.closePath()` | implemented |   |   
`VGContext.createImageData()` |   |   |   
`VGContext.createLinearGradient()` |   |   |   
`VGContext.createPattern()` |   |   |   
`VGContext.createRadialGradient()` |   |   |   
`VGContext.drawFocusIfNeeded()` |   |   |   
`VGContext.drawImage()` |   |   |   
`VGContext.drawWindow()` |   |   |   
`VGContext.ellipse()` |   |   |   
`VGContext.fill()` | API unfinished |   |   
`VGContext.fillRect()` | API unfinished |   |   
`VGContext.fillText()` | API unfinished |   |   
`VGContext.getImageData()` |   |   |   
`VGContext.getLineDash()` | API unfinished |   |   
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
`VGContext.restore()` | partly implemented |   |   
`VGContext.rotate()` |   |   |   
`VGContext.save()` | partly implemented |   |   
`VGContext.scrollPathIntoView()` |   |   |   
`VGContext.setLineDash()` | implemented |   |   
`VGContext.setTransform()` |   |   |   
`VGContext.stroke()` | API unfinished |   |   
`VGContext.strokeRect()` | API unfinished |   |   
`VGContext.strokeText()` | API unfinished |   |   
`VGContext.transform()` |   |   |   
`VGContext.translate()` |   |   |   
