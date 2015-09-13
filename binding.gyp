{
  "targets": [
    {
      "target_name": "vgcanvas",
      "sources": [
        "src/infoscreen.cc",
        "src/egl-util.c",
        "src/canvas.c",
        "src/color.c"
      ],
      "include_dirs": [
        "/opt/vc/include",
        "/opt/vc/include/interface/vmcs_host/linux",
        "/opt/vc/include/interface/vcos/pthreads"
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
          "-lrt"
        ],
        "library_dirs": [
          "/opt/vc/lib"
        ]
      }
    }
  ]
}
