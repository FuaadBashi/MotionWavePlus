cmake_minimum_required(VERSION 3.20)
project(MotionWavePlus LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

# Pure waveform geometry: no raylib, so it builds and tests anywhere.
add_library(motionwave_waveform STATIC src/render/Waveform.cpp)
target_include_directories(motionwave_waveform PUBLIC ${CMAKE_SOURCE_DIR}/src)
if(NOT MSVC)
    target_compile_options(motionwave_waveform PRIVATE -Wall -Wextra -Wpedantic)
endif()

option(MOTIONWAVE_BUILD_APP "Build the raylib visualiser" ON)
if(MOTIONWAVE_BUILD_APP)
    # Use an installed raylib 5 if there is one; otherwise download and build 5.5.
    find_package(raylib 5 QUIET)
    if(NOT raylib_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.5
            GIT_SHALLOW TRUE)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(raylib)
    endif()

    add_executable(MotionWavePlus src/main.cpp src/render/Renderer.cpp src/audio/AudioEngine.cpp)
    # miniaudio is vendored as a single header.
    target_include_directories(MotionWavePlus PRIVATE ${CMAKE_SOURCE_DIR}/src
                                                      ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(MotionWavePlus PRIVATE motionwave_waveform raylib Threads::Threads
                                                 ${CMAKE_DL_LIBS})
    if(APPLE)
        target_link_libraries(MotionWavePlus PRIVATE "-framework CoreAudio"
                                                     "-framework AudioToolbox")
    endif()
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(waveform_test tests/waveform_test.cpp)
    target_link_libraries(waveform_test PRIVATE motionwave_waveform)
    add_test(NAME waveform_test COMMAND waveform_test)

    add_executable(sample_exchange_test tests/sample_exchange_test.cpp)
    target_include_directories(sample_exchange_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(sample_exchange_test PRIVATE Threads::Threads)
    add_test(NAME sample_exchange_test COMMAND sample_exchange_test)
endif()
