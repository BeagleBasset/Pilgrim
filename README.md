# Pilgrim - Procedural OpenGL World Generator

This was a quick project I intended to finish during my holiday. It's a simple OpenGL procedural world generator based on Perlin noise.

The project could be greatly optimized and extended. I might get around to it on boring rainy days.


## Key Features

- **Procedural Terrain Generation** using Perlin noise
- **Infinite Chunk Loading**: Dynamic generation and unloading based on camera position
- **Water Shader** with subtle wave animation
- **First-Person Camera Controls** (WASD + mouse look)
- **Pause Functionality**: Pause the simulation with `P` key and overlay
- **Volumetric Clouds** using billboarding
## Requirements

This project requires the following external libraries:

- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [GLM](https://github.com/g-truc/glm)
- [stb_easy_font.h](https://github.com/nothings/stb)
- [sol-prog PerlinNoise](https://github.com/sol-prog/Perlin_Noise)

These libraries are **not included** in the repository.
You can install them using [vcpkg](https://github.com/microsoft/vcpkg) or manually.

## Build Instructions

This project uses **CMake** as its build system.

### Clone the repository

```bash
git clone https://github.com/BeagleBasset/Pilgrim.git
cd Pilgrim
```

### Create build directory and compile

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Run the application

Make sure your working directory is set correctly to find shaders and other resources.

## Contributing

Contributions are welcome! If you find bugs, have ideas for improvements, or just want to help out, feel free to open an issue or submit a pull request. 😄

This `Pilgrim` C++ project generated with CCPG.py.
