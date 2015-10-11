# node-vgcanvas

Node.js wrapper for Canvas 2D API targeting the Raspberry Pi. This wrapper uses OpenVG for performant GPU rendering.

## Canvas 2D API implementation status

Canvas 2D Method | C implementation | C++ wrapper implementation | Node.JS implementation
-----------------|------------------|----------------------------|-----------------------
`VGContext.canvas` |   |   |   
`VGContext.currentTransform` |   |   |   
`VGContext.direction` |   |   |   
`VGContext.fillStyle` | implemented | implemented | implemented
`VGContext.filter` |   |   |   
`VGContext.font` | implemented |   |   
`VGContext.globalAlpha` | implemented |  implemented | implemented
`VGContext.globalCompositeOperation` |   |   |   
`VGContext.imageSmoothingEnabled` |   |   |   
`VGContext.lineCap` | implemented | implemented | implemented
`VGContext.lineDashOffset` | implemented | implemented | implemented
`VGContext.lineJoin` | implemented | implemented | implemented
`VGContext.lineWidth` | implemented | implemented | implemented
`VGContext.miterLimit` | implemented |   |   
`VGContext.shadowBlur` |   |   |   
`VGContext.shadowColor` |   |   |   
`VGContext.shadowOffsetX` |   |   |   
`VGContext.shadowOffsetY` |   |   |   
`VGContext.strokeStyle` | implemented | implemented | implemented
`VGContext.textAlign` | implemented |   |   
`VGContext.textBaseline` | implemented |   |   
`VGContext.addHitRegion()` |   |   |   
`VGContext.arc()` | implemented | implemented | implemented
`VGContext.arcTo()` |   |   |   
`VGContext.asyncDrawXULElement()` |   |   |   
`VGContext.beginPath()` | implemented | implemented | implemented
`VGContext.bezierCurveTo()` | implemented | implemented | implemented
`VGContext.clearHitRegion()` |   |   |   
`VGContext.clearRect()` | implemented | implemented | implemented
`VGContext.clip()` | implemented | implemented | implemented
`VGContext.closePath()` | implemented | implemented | implemented
`VGContext.createImageData()` |   |   |   
`VGContext.createLinearGradient()` | implemented | implemented | implemented
`VGContext.createPattern()` |   |   |   
`VGContext.createRadialGradient()` | implemented | implemented | implemented
`VGContext.drawFocusIfNeeded()` |   |   |   
`VGContext.drawImage()` |   |   |   
`VGContext.drawWindow()` |   |   |   
`VGContext.ellipse()` |   |   |   
`VGContext.fill()` | implemented | implemented | implemented
`VGContext.fillRect()` | implemented | implemented | implemented
`VGContext.fillText()` | implemented |   |   
`VGContext.getImageData()` |   |   |   
`VGContext.getLineDash()` | implemented | implemented | implemented
`VGContext.isPointInPath()` |   |   |   
`VGContext.isPointInStroke()` |   |   |   
`VGContext.lineTo()` | implemented | implemented | implemented
`VGContext.measureText()` |   |   |   
`VGContext.moveTo()` | implemented | implemented | implemented
`VGContext.putImageData()` |   |   |   
`VGContext.quadraticCurveTo()` | implemented | implemented | implemented
`VGContext.rect()` | implemented | implemented | implemented
`VGContext.removeHitRegion()` |   |   |   
`VGContext.resetTransform()` |   |   |   
`VGContext.restore()` | partly implemented | implemented | implemented
`VGContext.rotate()` |   |   |   
`VGContext.save()` | partly implemented | implemented | implemented
`VGContext.scrollPathIntoView()` |   |   |   
`VGContext.setLineDash()` | implemented | implemented | implemented
`VGContext.setTransform()` |   |   |   
`VGContext.stroke()` | implemented | implemented | implemented
`VGContext.strokeRect()` | implemented | implemented | implemented
`VGContext.strokeText()` | implemented |   |   
`VGContext.transform()` |   |   |   
`VGContext.translate()` |   |   |   
