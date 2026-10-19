*This project has been created as part of the 42 curriculum by antbonin.*

# SCOP: Introduction to GPU Rendering

## Description
**SCOP** is an introductory project to the world of 3D graphics programming and the graphics pipeline. The main goal of this project is to build a basic 3D application capable of parsing a 3D model file (`.obj` format) and rendering it using a low-level graphics API. 

Instead of relying on heavy game engines or pre-built mathematical libraries, this project requires building the core rendering logic from scratch. This includes:
- Creating a custom 3D mathematics library (Vectors and 4x4 Matrices) to handle translations, rotations, and perspective projections without using external libraries like GLM.
- Writing a custom `.obj` file parser to extract vertex data and face indices, including automatic triangulation for polygonal faces.
- Managing GPU memory via Vertex Buffer Objects (VBO), Vertex Array Objects (VAO), and Element Buffer Objects (EBO).
- Writing custom GLSL Shaders to handle vertex positioning and fragment coloring.

The result is a lightweight, efficient 3D viewer that centers the model at the origin, displays it in a correct perspective projection, and makes it spin around its main axis.

### Technical Choices
- **Language:** C++17
- **Graphics API:** OpenGL 3.3 Core Profile
- **Window Management:** GLFW
- **Extension Loader:** GLAD

## Instructions

### Prerequisites
To compile and run this project, you need a C++ compiler (`c++`), `make`, and the GLFW3 library installed on your system.

On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install libglfw3-dev libgl1-mesa-dev xorg-dev
```

### Compilation
The project uses a standard Makefile. To compile the application, simply run:
```bash
make
```

This will produce an executable named `scop`.

### Execution
Run the program by passing a `.obj` file as an argument. If no argument is provided, the program can load a default model.

```bash
./scop resources/42.obj
```

**Controls:**
- `ESC`: Close the window.
- *(Add any other custom controls you implement here, e.g., T to toggle texture, Mouse/Arrows to move)*

## Resources

### Documentation & Tutorials
- [LearnOpenGL](https://learnopengl.com/) - The absolute best resource for understanding the modern OpenGL pipeline, Shaders, and matrix mathematics.
- [Wavefront .obj file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file) - Specification details for understanding how to parse vertices and faces.
- [OpenGL Reference Pages (docs.gl)](https://docs.gl/) - Quick and clean documentation for OpenGL API functions.

### AI Usage
Artificial Intelligence (LLM) was used as an interactive tutor and pair-programming assistant during the development of this project. Specifically, it was used for:
- Understanding the theoretical concepts of the OpenGL graphics pipeline (VAO, VBO, EBO, and the roles of Vertex/Fragment shaders) through analogies.
- Assisting in the architectural design of the C++ classes (RAII pattern for managing OpenGL resources like Shaders and Buffers).
- Formulating the mathematical logic for the custom `Mat4` class, particularly the complex matrix calculations required for the perspective projection and 3D rotations, bypassing the need for GLM.
- Writing the algorithm to parse `.obj` files and triangulate faces containing 4 vertices into standard 3-vertex triangles.