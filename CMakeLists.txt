cmake_minimum_required(VERSION 3.16)
project(PixelEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLAD
add_library(glad STATIC external/glad/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.9
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Fetch GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #1.0.1
)
FetchContent_MakeAvailable(glm)

# Executables
add_executable(pixel_engine 
  src/main.cpp
  src/core/Window.cpp
  src/core/Shader.cpp
  src/core/Mesh.cpp
)

target_include_directories(pixel_engine PRIVATE src)

target_link_libraries(pixel_engine
  PRIVATE
    glad
    glfw
    glm::glm
)

# copy shaders directory into build directory
add_custom_target(copy_shaders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/shaders
          ${CMAKE_BINARY_DIR}/shaders
  COMMENT "Copying shaders to build directory"
)