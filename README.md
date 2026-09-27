# MotionWave+ — C++ Audio Visualization

A C++20 audio-visualization prototype that combines raylib rendering with miniaudio playback and shares decoded samples with the renderer.

## Build

Requires CMake 3.20+, a C++20 compiler, and raylib discoverable by CMake.

```bash
git clone https://github.com/FuaadBashi/MotionWavePlus.git
cd MotionWavePlus
cmake -S . -B build-local -DCMAKE_BUILD_TYPE=Release
cmake --build build-local
```

## Audio setup and launch

Before building, replace the hard-coded audio path in [src/main.cpp](src/main.cpp) with a local WAV file. Audio files are not bundled.

```bash
./build-local/MotionWavePlus
```

The build target is `MotionWavePlus`.

## Code to explore

- [src/main.cpp](src/main.cpp): initialization, render loop, and shutdown.
- [src/audio](src/audio): miniaudio integration and shared sample state.
- [src/render](src/render): visualization rendering.
- [CMakeLists.txt](CMakeLists.txt): dependencies and target definition.

This is a desktop prototype. Audio initialization, callback bounds, and shutdown behavior need further validation; no real-time safety or performance benchmark is claimed.
