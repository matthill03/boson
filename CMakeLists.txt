cmake_minimum_required(VERSION 3.20)
project(boson VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Include FetchContent to manage external dependencies
include(FetchContent)

# Set the base director for external libraries
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR}/external)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/glfw
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Fetch GLEW
FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG glew-cmake-2.2.0
    SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/glew
)
FetchContent_MakeAvailable(glew)

# Fetch and configure GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# Fetch Assimp
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.4.3
    SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/assimp
)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

# Automatically add all .cpp files in the src directory
file(GLOB_RECURSE SOURCES src/*.cpp src/*/*.cpp)

# Add the executable for the project
add_library(${PROJECT_NAME} ${SOURCES})

# Define necessary compile definitions for GLEW
target_compile_definitions(${PROJECT_NAME} PRIVATE
    GLEW_STATIC
    GL_GLEXT_PROTOTYPES
)

# Link the necessary libraries (OpenGL, glfw, glew, glm, json, assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    libglew_static
    glm::glm
    # nlohmann_json::nlohmann_json
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    assimp
)

# Add include directories for the project and the fetched libraries
target_include_directories(${PROJECT_NAME} PRIVATE
    ${FETCHCONTENT_BASE_DIR}/glfw/include
    ${FETCHCONTENT_BASE_DIR}/glm
    # ${FETCHCONTENT_BASE_DIR}/glew/include
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${FETCHCONTENT_BASE_DIR}/assimp/include
)

# Optional: Platform-specific frameworks for macOS
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()

# Optional: Platform-specific libraries for Linux
if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${OPENGL_LIBRARIES}
        dl
        pthread
    )
endif()

# Optional: Platform-specific libraries for Windows
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32
    )
endif()


