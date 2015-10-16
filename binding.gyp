{
  "targets": [
    {
      "target_name": "vgcanvas",
      "sources": [
        "src/vgcanvas.cc",
        "src/gradient.cc",
        "src/canvas-arc.c",
        "src/canvas-beginPath.c",
        "src/canvas-bezierCurveTo.c",
        "src/canvas-clearRect.c",
        "src/canvas-clip.c",
        "src/canvas-closePath.c",
        "src/canvas-fill.c",
        "src/canvas-fillRect.c",
        "src/canvas-fillStyle.c",
        "src/canvas-fillText.c",
        "src/canvas-font.c",
        "src/canvas-globalAlpha.c",
        "src/canvas-globalCompositeOperation.c",
        "src/canvas-kerning.c",
        "src/canvas-lineCap.c",
        "src/canvas-lineDashOffset.c",
        "src/canvas-lineJoin.c",
        "src/canvas-lineTo.c",
        "src/canvas-lineWidth.c",
        "src/canvas-measureText.c",
        "src/canvas-miterLimit.c",
        "src/canvas-moveTo.c",
        "src/canvas-paint.c",
        "src/canvas-quadraticCurveTo.c",
        "src/canvas-rect.c",
        "src/canvas-resetTransform.c",
        "src/canvas-restore.c",
        "src/canvas-rotate.c",
        "src/canvas-save.c",
        "src/canvas-scale.c",
        "src/canvas-setLineDash.c",
        "src/canvas-setTransform.c",
        "src/canvas-stroke.c",
        "src/canvas-strokeRect.c",
        "src/canvas-strokeStyle.c",
        "src/canvas-strokeText.c",
        "src/canvas-textAlign.c",
        "src/canvas-textBaseline.c",
        "src/canvas-transform.c",
        "src/canvas-translate.c",
        "src/canvas.c",
        "src/egl-util.c",
        "src/font-util.c"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "/opt/vc/include",
        "/opt/vc/include/interface/vmcs_host/linux",
        "/opt/vc/include/interface/vcos/pthreads",
        "/usr/include/freetype2"
      ],
      "link_settings": {
        "libraries": [
          "-lm",
          "-lGLESv2",
          "-lEGL",
          "-lopenmaxil",
          "-lbcm_host",
          "-lvcos",
          "-lvchiq_arm",
          "-lpthread",
          "-lrt",
          "-lfreetype"
        ],
        "library_dirs": [
          "/opt/vc/lib"
        ]
      },
      "cflags_c": [ "-fgnu89-inline" ] # fix for vcos compiler warnings
    }
  ]
}
