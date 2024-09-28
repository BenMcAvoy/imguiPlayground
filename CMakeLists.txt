cmake_minimum_required(VERSION 3.5)
project(imguiPlayground)

# Configure C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatic LSP configuration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# vendor/glfw
add_subdirectory(vendor/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# vendor/imgui
file (GLOB IMGUI_SOURCES vendor/imgui/*.cpp)
list (APPEND IMGUI_SOURCES vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp)

file (GLOB IMGUI_HEADERS vendor/imgui/*.h)
list (APPEND IMGUI_HEADERS vendor/imgui/backends/imgui_impl_glfw.h vendor/imgui/backends/imgui_impl_opengl3.h)

include_directories(vendor/imgui)
add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})

# vendor/glad
file(GLOB_RECURSE GLAD_SOURCES vendor/glad/src/*.c)
file(GLOB_RECURSE GLAD_HEADERS vendor/glad/include/*.h)

add_library(glad STATIC ${GLAD_SOURCES} ${GLAD_HEADERS})

target_include_directories(glad PUBLIC vendor/glad/include)

# vendor/spdlog
add_subdirectory(vendor/spdlog)
include_directories(vendor/spdlog/include)

# executable
file (GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(vendor/glfw/include vendor/glad/include vendor/spdlog/include vendor include)
target_link_libraries(${PROJECT_NAME} glfw glad imgui spdlog)
