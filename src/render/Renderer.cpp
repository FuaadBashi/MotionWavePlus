#include "Renderer.h"

#include "Waveform.h"
#include "audio/AudioData.h"
#include "raylib.h"

void Renderer::draw(AudioData *audio) {
    // Copy the latest block out and draw from the copy, so the buffer is held only for a memcpy.
    float local[SampleExchange::kCapacity];
    const int size = audio->visual.copyLatest(local);

    const float width = static_cast<float>(GetScreenWidth());
    const float height = static_cast<float>(GetScreenHeight());
    const std::vector<Point> points = waveformPoints(local, size, width, height, height * 0.28f);
    for (std::size_t i = 1; i < points.size(); ++i) {
        DrawLineEx({points[i - 1].x, points[i - 1].y}, {points[i].x, points[i].y}, 2.0f, ORANGE);
    }
}
