#include "audio/AudioData.h"
#include "audio/AudioEngine.h"
#include "raylib.h"
#include "render/Renderer.h"

#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <audio file: .wav, .mp3 or .flac>\n";
        return 1;
    }

    AudioData audio_data;
    if (!initAudio(&audio_data, argv[1])) {
        return 1;
    }

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "MotionWave+");
    SetTargetFPS(60);

    Renderer renderer;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground({13, 27, 42, 255});
        renderer.draw(&audio_data);
        DrawText(audio_data.finished ? "Finished - press Esc to quit" : "Esc to quit", 20, 20, 20,
                 GRAY);
        EndDrawing();
    }

    CloseWindow();
    cleanupAudio(&audio_data);
    return 0;
}
