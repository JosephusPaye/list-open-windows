{
  "targets": [
    {
      "target_name": "listOpenWindows",
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "sources": [
        "src/addon.cpp",
        "src/list-windows.cpp",
        "src/list-windows.js.cpp"
      ],
      "include_dirs": ["<!(node -p \"require('node-addon-api').include_dir\")"],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
    }
  ]
}
