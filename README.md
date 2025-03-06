# boson
Welcome to boson!! A library for using JSON Lines to describe 3D scenes in OpenGL. Trying to lower the barriers programmers may face when wanting to learn graphics programming. Allowing for the quick and easy description of scenes, while give control to the user.

## Table of Contents
- [Usage](#usage)
    - [Example Project](#example-project)
        - [Windows](#windows)
        - [Linux](#linux)
        - [MacOS](#MacOS)
    - [Library](#library)
- [Guide](#guide)
- [Features](#features)
- [Future Improvements](#future-improvements)

## Usage
### Example Project
The presets described are listed in the ```CMakePresets.json``` file.

#### Windows
Clone the example project.
```bash
git clone https://github.com/matthill03/boson-test.git
```
Open this new folder in VS Code.
```bash
cd boson-test
code .
```
Make sure that the CMake Tools extension is installed on VS Code.
This will then automatically detect the CMake project and ask you which preset you would like to use. Select ```windows```.

If this does NOT happen, open the command prompt and select ```CMake: Select Configure Preset```, then select ```windows```.

On the left hand side is the CMake Tools icon, select this. Then under ```Project Outline```, select ```Configure All Projects```.
Then ```Build All Projects```. Finally run the new executable ```test.exe```

#### Linux
Clone the example project.
```bash
git clone https://github.com/matthill03/boson-test.git
```
This project is set up where you do not have to download or build external dependencies yourself.
```bash
cd boson-test
cmake --preset linux
cd build
make
```
Then run the project using the ```test``` executable in the build folder.
```bash
./test
```
#### MacOS
Clone the example project.
```bash
git clone https://github.com/matthill03/boson-test.git
```
This project is set up where you do not have to download or build external dependencies yourself.
```bash
cd boson-test
cmake --preset macos
cd build
make
```
Then run the project using the ```test``` executable in the build folder.
```bash
./test
```

### Library
An example of how to build and include the library is shown in the example project. But here is an example ```CMakeLists.txt``` file to show how to use the project as a library.

#### CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.20)
project(test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/boson)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE boson)
```
This example is universal for Windows, Linux, and MacOS.

#### main.cpp
To use the library, follow the example bellow. The file path for the example scene is from the example project.

```c++
#include "boson/application.h"

int main() {
    boson::Application app("../examples/basic_scene.jsonl");
    app.run();
    return 0;
}
```
## Guide
### Object Types
#### Window
```json
{"type": "window", "width": int, "height": int, "title": string, "background_colour": {"r": float, "g": float, "b": float}}
```
Example Parameters:
- type: "window"
- width: 1280
- height: 720
- title: "Hello Window"
- background_colour: {"r": 0.5, "g": 0.8, "b": 0.3}

#### Shader
```json
{"type": "shader", "vertex_shader": string, "fragment_shader": string}
```
Example Parameters:
- type: "shader"
- vertex_shader: "<path_to_boson_lib>/resources/shaders/default_vertex.glsl"
- fragment_shader: "<path_to_boson_lib>/resources/shaders/default_fragment.glsl"

To create your own shaders please use the template below. As there are parameters the library needs to set lights, materials and more.

Fragment Shader:
```glsl
```
Vertex Shader:
```glsl
```
#### Camera
```json
{"type": "camera", "position": {"x": float, "y": float, "z": float}, "focus_point": {"x": float, "y": float, "z": float}, "fov": int }
```
Example Parameters:
- type: "camera"
- position: {"x": 6.0, "y": 3.0, "z": 10.0}
- focus_point: {"x": 0.0, "y": 3.0, "z": 0.0}
- fov: 45

#### Texture
```json
{"type": "texture", "name": string, "file_path": string, "texture_type": string}
```
Texture types:
- diffuse
- specular

Example Parameters:
- type: "texture"
- name: "texture_one"
- file_path: "<path_to_texture>"
- texture_type: "diffuse"

#### Texture Set
```json
{"type": "texture_set", "name": string, "textures": string[]}
```
Example Parameters:
- type: "texture_set"
- name: "box_textures"
- textures: \["texture_one", "texture_two"\]

#### Material
```json
{"type": "material", "name": string, "ambient": {"r": float, "g": float, "b": float}, "diffuse": {"r": float, "g": float, "b": float}, "specular": {"r": float, "g": float, "b": float}, "shininess": float}
{"type": "material", "name": string, "textures": string, "shininess": float}
```
There are two options when defining a material, if there are textures given then this will overwirte the colours given.

Example Parameters (Colour Material):
- type: "material"
- name: "colour_example"
- ambient: {"r": 0.8, "g": 0.8, "b": 0.8}
- diffuse: {"r": 0.6, "g": 0.6, "b": 0.6}
- specular: {"r": 0.2, "g": 0.2, "b": 0.2}
- shininess: 1.0

Example Parameters (Texture Material):
- type: "material"
- name: "texture_example"
- textures: "box_textures"
- shininess: 32.0

#### Shapes
##### Cube
```json
{"type": "cube", "name": string, "position": {"x": float, "y": float, "z": float}, "size": {"x": float, "y": float, "z": float}, "rotation": {"x": float, "y": float, "z": float}, "material": string}
```
Example Parameters:
- type: "cube"
- name: "cube_one"
- position: {"x": 4.0, "y": -0.5, "z": 5.0}
- size: {"x": 1.0, "y": 1.0, "z": 1.0}
- rotation: {"x": 0.0, "y": 45.0, "z": 0.0}
- material: "colour_example"

##### Model
```json
{"type": "model", "name": string, "position": {"x": float, "y": float, "z": float}, "size": {"x": float, "y": float, "z": float}, "rotation": {"x": float, "y": float, "z": float}, "file_path": string}
```
Example Parameters:
- type: "model"
- name: "latern"
- position: {"x": 6.0, "y": -1.0, "z": 3.0}
- size: {"x": 0.2, "y": 0.2, "z": 0.2}
- rotation: {"x": 0.0, "y": 180.0, "z": 0.0}
- file_path: "../resources/lateran/Lantern.gltf"

##### Plane
```json
{"type": "plane", "name": string, "position": {"x": float, "y": float, "z": float}, "size": {"x": float, "y": float}, "rotation": {"x": float, "y": float, "z": float}, "tile_count": {"x": float, "y": float}, "material": string}
```
Example Parameters:
- type: "plane"
- name: "plane_one"
- position: {"x": 0.0, "y": -1.0, "z": 0.0}
- size: {"x": 5.0, "y": 5.0}
- rotation: {"x": 0.0, "y": 0.0, "z": 0.0}
- tile_count: {"x": 1.0, "y": 1.0}
- material: "default"

##### Sphere

##### Cylinder

#### Light
##### directional
```json
{"type": "light", "light_kind": "directional", "direction": {"x": float, "y": float, "z": float}, "ambient": {"r": float, "g": float, "b": float}, "diffuse": {"r": float, "g": float, "b": float}, "specular": {"r": float, "g": float, "b": float}}
```
Example Parameters:
- type: "light"
- light_kind: "directional"
- direction: {"x": 0.0, "y": -10.0, "z": -8.0}
- ambient: {"r": 0.2, "g": 0.2, "b": 0.2}
- diffuse: {"r": 0.8, "g": 0.8, "b": 0.8}
- specular: {"r": 0.3, "g": 0.3, "b": 0.3}

##### point
```json
{"type": "light", "light_kind": "point", "position": {"x": float, "y": float, "z": float}, "constant": float, "linear": float, "quadratic": float, "ambient": {"r": float, "g": float, "b": float}, "diffuse": {"r": float, "g": float, "b": float}, "specular": {"r": float, "g": float, "b": float}}
```
Example Parameters:
- type: "light"
- light_kind: "point"
- position: {"x": 0.0, "y": 2.0, "z": 3.0}
- constant: 1.0
- linear: 0.02
- quadratic: 0.09
- ambient: {"r": 0.2, "g": 0.2, "b": 0.2}
- diffuse: {"r": 0.8, "g": 0.8, "b": 0.8}
- specular: {"r": 0.3, "g": 0.3, "b": 0.3}

#### Skybox
```json
{"type": "skybox", "faces": string[6]}
```
Example Parameters:
- type: "skybox"
- faces: \["../resources/skybox/right.jpg", "../resources/skybox/left.jpg", "../resources/skybox/top.jpg", "../resources/skybox/bottom.jpg", "../resources/skybox/front.jpg", "../resources/skybox/back.jpg"\]

## Features

## Future Improvements
