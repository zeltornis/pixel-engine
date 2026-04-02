# Pixel Engine

A minimalistic OpenGL graphics engine made to be a sandbox for trying out shaders, and as a learning project. Intended to be a base for more sophisticated graphics engines.
Built with GLFW, GLAD, and GLM.

## Project Structure

```
project_root/
├── external/
│   └── glad/                  # Vendored GLAD (see note below)
│       ├── glad.c
│       └── include/
│           ├── glad/glad.h
│           └── KHR/khrplatform.h
├── src/
│   ├── core/
│   │   ├── Window.cpp / .hpp
│   │   ├── Shader.cpp / .hpp
│   │   └── Mesh.cpp / .hpp
│   └── main.cpp
├── shaders/
│   ├── basic.vert
│   └── basic.frag
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## Features
- Window abstraction (Window class)
- Shader abstraction (Shader class)
- Mesh abstraction (Mesh class) for VAO/VBO/EBO
- Example shaders (vertex + fragment) with time and resolution uniforms

## Requirements
- CMake 3.16+
- C++17 compiler
  - Linux: GCC or Clang
  - Windows: Visual Studio 2019+ or MinGW-w64
- Git (so CMake can fetch dependencies)
- Dependencies fetched automatically by CMake:
  - GLFW
  - GLM
- GLAD files are included with the project

### GLAD

The GLAD files in `external/glad/` were generated at https://glad.dav1d.de
with the following settings:

- **Language:** C/C++
- **Specification:** OpenGL
- **API gl:** Version 3.3
- **Profile:** Core
- **Extensions:** *(none)*
- **Generate a loader:** checked

If you need to regenerate GLAD (e.g. to add extensions or change the GL
version), use the same site and replace the files in `external/glad/`.

## Build Instructions

### Linux / macOS

```bash
git clone https://github.com/zeltornis/pixel-engine.git
cd PixelEngine
cmake -B build -G Ninja          # or omit -G to use the default generator
cd build
cmake --build .
./pixel_engine
```

### Windows (Visual Studio)

```bat
git clone https://github.com/zeltornis/pixel-engine.git
cd PixelEngine
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
build\Release\pixel_engine.exe
```

### Windows (Ninja + MSVC)

Open a **Developer Command Prompt for VS**, then:

```bat
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
build\pixel_engine.exe
```

> **Note:** Shaders are copied automatically next to the executable after
> each build, so you can run the binary from any working directory.