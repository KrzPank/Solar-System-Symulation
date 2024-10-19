# Solar-System-Symulation
My introductory project to learn OpenGL. With help of learnopengl.com and youtube.com/@VictorGordan OpenGl tutorials.

This project is a real-time simulation of the Solar System, developed in C++ using OpenGL. The simulation includes camera manipulation, lighting, and textured planets. The project also makes use of custom shaders for rendering.

## Features

- **Solar System Simulation**: Includes various planets, each orbiting the sun with realistic scales and distances.
- **Camera Manipulation**: Freely move the camera to observe the simulation from different perspectives.
- **Lighting Source**: The sun acts as a dynamic light source, affecting the appearance of the planets.
- **Textured Planets**: Each planet is mapped with textures to create a realistic appearance.
- **Custom Shaders**: Vertex and fragment shaders are used to handle lighting, texture, and rendering of 3D objects.
- **.OBJ Loader**: Basic support for loading and rendering `.obj` 3D models.
- **ImGui Interface**:
  - Change view between different planets.
  - Adjust simulation speed.

## Technologies Used

- **C++**: Core programming language for the project.
- **OpenGL**: Used for rendering the 3D scene and handling graphics.
- **GLFW**: For window management and input handling.
- **GLM**: For mathematical operations such as matrix and vector manipulation.
- **GLAD**: For handling OpenGL function loading and extensions.
- **ImGui**: GUI framework for interactive controls.
- **STB**: Image loading for textures.
- **Custom Shaders**: Written in GLSL for handling lighting, textures, and rendering.
- **OBJ Loader**: Basic loader to render additional 3D models from `.obj` files.

### Prerequisites

- [GLFW](https://www.glfw.org/) (Window management and input handling)
- [GLAD](https://glad.dav1d.de/) (OpenGL function loader)
- [GLM](https://github.com/g-truc/glm) (Math library for 3D transformations)
- [stb_image](https://github.com/nothings/stb) (Image loading library)
- [ImGui](https://github.com/ocornut/imgui) (GUI)

**Clone the repository**:
  ```bash
  $ git clone https://github.com/KrzPank/Solar-System-Symulation.git
  ```
### Running

To run the simulation, you can either:

1. **Run the compiled executable**:
    ```bash
    .src/main.exe
    ```
   
2. **Compile and run using VS Code tasks**:
    - Open the project in VS Code.
    - Use the **Run and Debug** panel or the **Tasks** feature in VS Code to build and run the project.
    - Make sure you have configured a `tasks.json` and `launch.json` in the `.vscode/` directory for automated building and execution.

### Controls

#### Camera Controls
- `W`, `A`, `S`, `D`: Move the camera forward, left, backward, and right.
- `Q`, `E`: Move the camera up and down.
- `Space`: Move the camera up.
- `Ctrl`: Move the camera down.
- `Shift`: Move faster.
- Mouse movement: Rotate the camera.
- Scroll: Zoom in/out.

### .OBJ Loader

The simulation includes a basic `.obj` loader that allows you to import and render 3D models.

You can load your own `.obj` files by placing them in the `resources/models/` directory and updating the file paths in the code.

> **Warning**: Only **triangulated** `.obj` models are supported. Ensure that any models you use are properly triangulated, as non-triangulated models will not render.


## Project Structure

- `.vscode/`: Contains configuration files for building and running the project in VS Code.
  - `settings.json`: Project-specific settings for VS Code.
  - `tasks.json`: Task configurations for compiling and running the project.
- `include/`: Header files for the simulation.
- `lib/`: Library files.
  - `libglfw3dll.a`: GLFW library.
- `src/`: Source files for the simulation.
  - `resources/`: Contains all assets used in the simulation:
    - `shaders/`: Vertex and fragment shaders used for rendering.
    - `images/`: Textures applied to the planets and the sun.
    - `models/`: 3D `.obj` models.

---

**Author**: [Krzysztof Pankiewicz](https://www.linkedin.com/in/krzysztof-pankiewicz-71424b329/)
