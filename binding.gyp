{
    "targets": [
        {
            "target_name": "listOpenWindows",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": ["<!@(node -p \"require('fs').readdirSync('./src').filter(f=>f.endsWith('.cpp')).map(f=>'src/'+f).join(' ')\")" ],
            "include_dirs": ["<!(node -p \"require('node-addon-api').include_dir\")"],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        }
    ]
}
