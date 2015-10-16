# node-vgcanvas

Node.js wrapper for Canvas 2D API targeting the Raspberry Pi. This wrapper uses OpenVG for performant GPU rendering.

## Canvas 2D API implementation status

Canvas 2D Method | C implementation | C++ wrapper implementation | Node.JS implementation
-----------------|------------------|----------------------------|-----------------------
`VGContext.canvas` | *nothing to implement* | pending | pending 
`VGContext.currentTransform` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.direction` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.fillStyle` | **implemented** | **implemented** | **implemented**
`VGContext.filter` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.font` | **implemented** | pending | pending 
`VGContext.globalAlpha` | **implemented** |  **implemented** | **implemented**
`VGContext.globalCompositeOperation` | pending | pending | pending 
`VGContext.imageSmoothingEnabled` | pending | pending | pending 
`VGContext.lineCap` | **implemented** | **implemented** | **implemented**
`VGContext.lineDashOffset` | **implemented** | **implemented** | **implemented**
`VGContext.lineJoin` | **implemented** | **implemented** | **implemented**
`VGContext.lineWidth` | **implemented** | **implemented** | **implemented**
`VGContext.miterLimit` | **implemented** | pending | pending 
`VGContext.shadowBlur` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.shadowColor` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.shadowOffsetX` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.shadowOffsetY` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.strokeStyle` | **implemented** | **implemented** | **implemented**
`VGContext.textAlign` | **implemented** | pending | pending 
`VGContext.textBaseline` | **implemented** | pending | pending 
`VGContext.addHitRegion()` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.arc()` | **implemented** | **implemented** | **implemented**
`VGContext.arcTo()` | pending | pending | pending 
`VGContext.beginPath()` | **implemented** | **implemented** | **implemented**
`VGContext.bezierCurveTo()` | **implemented** | **implemented** | **implemented**
`VGContext.clearHitRegion()` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.clearRect()` | **implemented** | **implemented** | **implemented**
`VGContext.clip()` | **implemented** | **implemented** | **implemented**
`VGContext.closePath()` | **implemented** | **implemented** | **implemented**
`VGContext.createImageData()` | pending | pending | pending 
`VGContext.createLinearGradient()` | **implemented** | **implemented** | **implemented**
`VGContext.createPattern()` | pending | pending | pending 
`VGContext.createRadialGradient()` | **implemented** | **implemented** | **implemented**
`VGContext.drawFocusIfNeeded()` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.drawImage()` | pending | pending | pending 
`VGContext.drawWindow()` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.ellipse()` | pending | pending | pending 
`VGContext.fill()` | **implemented** | **implemented** | **implemented**
`VGContext.fillRect()` | **implemented** | **implemented** | **implemented**
`VGContext.fillText()` | **implemented** | pending | pending 
`VGContext.getImageData()` | pending | pending | pending 
`VGContext.getLineDash()` | **implemented** | **implemented** | **implemented**
`VGContext.isPointInPath()` | pending | pending | pending 
`VGContext.isPointInStroke()` | pending | pending | pending 
`VGContext.lineTo()` | **implemented** | **implemented** | **implemented**
`VGContext.measureText()` | **implemented** | pending | pending 
`VGContext.moveTo()` | **implemented** | **implemented** | **implemented**
`VGContext.putImageData()` | pending | pending | pending 
`VGContext.quadraticCurveTo()` | **implemented** | **implemented** | **implemented**
`VGContext.rect()` | **implemented** | **implemented** | **implemented**
`VGContext.removeHitRegion()` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.resetTransform()` | **implemented** | pending | pending 
`VGContext.restore()` | **partly implemented** | **implemented** | **implemented**
`VGContext.rotate()` | **implemented** | pending | pending 
`VGContext.save()` | **partly implemented** | **implemented** | **implemented**
`VGContext.scale()` | **implemented** | pending | pending 
`VGContext.scrollPathIntoView()` | *won't implement* | *won't implement* | *won't implement* 
`VGContext.setLineDash()` | **implemented** | **implemented** | **implemented**
`VGContext.setTransform()` | **implemented** | pending | pending 
`VGContext.stroke()` | **implemented** | **implemented** | **implemented**
`VGContext.strokeRect()` | **implemented** | **implemented** | **implemented**
`VGContext.strokeText()` | **implemented** | pending | pending 
`VGContext.transform()` | **implemented** | pending | pending 
`VGContext.translate()` | **implemented** | pending | pending 
