cmake_minimum_required(VERSION 3.20)
project(MotionWavePlus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(MotionWavePlus 
    src/main.cpp
    src/render/Renderer.cpp
    src/audio/AudioEngine.cpp
)

target_include_directories(MotionWavePlus PRIVATE ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(MotionWavePlus PRIVATE raylib)


