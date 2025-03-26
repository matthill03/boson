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
    - [Object Type](#object-types)
        - [Window](#window)
        - [Shader](#shader)
        - [Camera](#camera)
        - [Texture](#texture)
        - [Texture Set](#texture-set)
        - [Material](#material)
        - [Shapes](#shapes)
            - [Cube](#cube)
            - [Model](#model)
            - [Plane](#plane)
            - [Sphere](#sphere)
            - [Cylinder](#cylinder)
        - [Light](#light)
            - [Directional](#directional)
            - [Point](#point)
        - [Skybox](#skybox)
- [Features](#features)
- [Future Improvements](#future-improvements)

## Usage
### Example Project
The presets described are listed in the ```CMakePresets.json``` file.

#### Windows
Clone the example project and initialise the submodle.
```bash
git clone https://github.com/matthill03/boson-test.git
cd boson-test
git submodule update --init --recursive
```
Open this new folder in VS Code.
```bash
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
The window object should be the **first** object listed in the JSONL file. This is where the scene will be displayed. The width and height of the window will affect the aspect ratio of the camera.
```
{"type": "window", "width": int, "height": int, "title": string, "background_colour": {"r": float, "g": float, "b": float}}
```
Example Parameters:
- type: "window"
- width: 1280
- height: 720
- title: "Hello Window"
- background_colour: {"r": 0.5, "g": 0.8, "b": 0.3}

#### Shader
The shader given is the shader used for rendering. There is **no** way of using a shader per object. The fragment shader and vertex shader given are the file paths to each of the shaders for the program.
```
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
This is the view port of the scene, this has to be defined **after** the shader of the program as the parameters are passed into the shader upon creation. The position is the position of the camera in world space and the focus point is where the camera is looking.
```
{"type": "camera", "position": {"x": float, "y": float, "z": float}, "focus_point": {"x": float, "y": float, "z": float}, "fov": int }
```
Example Parameters:
- type: "camera"
- position: {"x": 6.0, "y": 3.0, "z": 10.0}
- focus_point: {"x": 0.0, "y": 3.0, "z": 0.0}
- fov: 45

#### Texture
Textures are used to load images into the program and use them as texture maps for materials. These cannot be directly added onto shapes or objects but can be used in textures sets. Each texture has a type, this is the type of lighting this texture is to be used for mapping.
```
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
Texture sets are a collection of textures used in materials. You can add as many textures to a texture set as you like, however, the last texture of each type is the one used in the scene. This will be improved on in the future.
```
{"type": "texture_set", "name": string, "textures": string[]}
```
Example Parameters:
- type: "texture_set"
- name: "box_textures"
- textures: \["texture_one", "texture_two"\]

#### Material
Materials can be applied to any shape/object in the scene. There are two 'types' of material. A colour material, or a textured material. Within the definition of the material you can define all aspects of the material, however, if textures are defined this will override the colour that may have been defined also.
```
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
These are the basic cube shape, you can specifiy all properties of the cube within the JSONL file. If the material is not given, a default material will be used by the library.
```
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
You can load any OBJ or GLTF model into the program. Textures may be loaded from the model file or can be defined manually by the user. In the example scene there is an example of both of these cases. When defining two objects of the same file path, please make sure to use the exact same file path in the definition.
```
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
This is a simple 2D plane that can be defined, you are able to define all attributes for this in the JSONL file. Planes have the ability to tile the textures given in the material, the number given in the tile count is how many times the texture will repeat on the given axis.
```
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
**NOT ADDED TO JSONL YET**

##### Cylinder
**NOT ADDED TO JSONL YET**

#### Light
##### directional
The directional lights are used for more ambient lighting for the scene, they simulate more of what the sun would do. All of the options shown bellow are required for the definition.
```
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
Point lights are normally used for more close up lighting, they simulate more of what a light bulb would look like. The linear, quadratic and constant values affect the attenuation of the light and the drop off in lighting from the source.
```
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
The skybox is used for the 'background' of the scene. The faces described for the cubemap are required to be in a specific order. That order is: right, left, top, bottom, front, and back.
```
{"type": "skybox", "faces": string[6]}
```
Example Parameters:
- type: "skybox"
- faces: \["../resources/skybox/right.jpg", "../resources/skybox/left.jpg", "../resources/skybox/top.jpg", "../resources/skybox/bottom.jpg", "../resources/skybox/front.jpg", "../resources/skybox/back.jpg"\]

## Features
There are a few key features that have been given to this project, some are graphics/rendering focused but others are for scene description.

- Instanced/Batch rendering
    - This has been implemented for all objects within the scene.
    - This gives a greated possibility for having more objects being rendered at the same time.
    - Also provides easier additions in the future like the grid object mentioned bellow.
- Materials/textures treated like variables
    - This gives reusable objects within the JSONL file.
    - Makes the JSONL file more readable and transferable.
- Use of texture sets
    - This gives the ability to reuse textures for different materials.
    - More verbose about which textures are used for which materials.
- GLTF/OBJ model loading
    - Objects can be loaded from common model files.
    - Textures can be defined in these files, but also can be manual specified in the JSONL file.
    - Models are batch rendered, meaning **one** VAO is used per model.
        - This may have to be re-thought when creating dynamic objects and using a scene graph.
- Cross-Platform Library

## Future Improvements
There are a few future improvements that are thought about already. As this is a dissertation project, not all possible features will have been added.

- Extra JSONL Objects
    - More JSONL objects for shapes and possible 'formatting' of objects in the scene such as a grid object.
    - This would give a few more possibilites on how the scene can be created and possible the concise nature of the JSONL file.
- Dynamic Scene
    - There is planned for the user to be able to interact with the objects they define in the scene.
    - This is so movement, logic and other features can be created by the user.
- User Created Shaders
    - If the user would like to use this as a shader playground. Giving them the ability to define and create their own shaders would be useful.
    - This would involve having a system to know wich objects use which shader and maybe moving away from there being a scene wide shader.
    - Give the user the ability to define uniforms or other shader input in the JSONL file.
- Optimisation in Rendering
    - Model loading and other optimisations need to be looked into.
    - This is less needed as there are other features that could be added before this being needed.
- Multiple Scenes in an Application
    - If this was to be used as a game framework/engine, needing multiple scenes within the application is important.
    - Would need to evolve multiple systems like textures and materials so these could be used across scenes.
    - Maybe some sort of 'include' system for the JSONL files where you can include another material and texture file for use.
- Use Vulkan in place of OpenGL
    - Due to this being a dissertation project OpenGL allowed for speed of development.
    - The 'simpler' understanding of OpenGL meant more features could be added.
    - Updating to vulkan would mean more modern rendering features and techniques
