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

## Features

## Future Improvements
