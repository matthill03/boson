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
```bash
 
```
### main.cpp
```c++
```

## Guide

## Features

## Future Improvements
