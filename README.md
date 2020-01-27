# emscripten-targz

```
emcc -std=c++17 -s USE_ZLIB=1 -s ASYNCIFY=1 -s NO_EXIT_RUNTIME=1 -O3 main.cc -o example.js
python3 -m http.server 8000
```

[http://127.0.0.1:8000](http://127.0.0.1:8000)

## Authorship

Matthew Andres Moreno

`m.more500@gmail.com`
