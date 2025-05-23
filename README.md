#### 1. Compile: type your path to SDL2 lib

For MSVC:

```bash
cl /EHsc /I"YOUR_PATH\SDL2-2.32.4\include" /Iinclude src\main.cpp src\gameoflife.cpp /link /LIBPATH:"YOUR_PATH\SDL2-2.32.4\lib\x86" SDL2.lib SDL2main.lib Shell32.lib /SUBSYSTEM:CONSOLE /OUT:gameoflife.exe

```

For MinGW:

```bash
g++ src/main.cpp src/gameoflife.cpp -Iinclude -IYOUR_PATH\SDL2-2.32.4\include -LYOUR_PATH\SDL2-2.32.4\lib\x64 -o gameoflife.exe -lSDL2main -lSDL2 -lShell32

```

#### 2. Run programm

```bash
gameoflife.exe
```
