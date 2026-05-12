#include "raylib.h"
#include "audio/AudioData.h"
#include "audio/AudioEngine.h"
#include "render/Renderer.h"


int main() {
    InitWindow(1280, 720, "MotionWave+");
    SetTargetFPS(60);

    AudioData audio_data;
    audio_data.sample_count = 0;
    initAudio(&audio_data, "/Users/fuaadshurie/Desktop/Life is Beautiful.wav");
    Renderer renderer;
    renderer.init();

    while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground({13, 27, 42, 255});
    renderer.draw(&audio_data);
    EndDrawing();
    }       

    cleanupAudio();
    CloseWindow();
    return 0;
}