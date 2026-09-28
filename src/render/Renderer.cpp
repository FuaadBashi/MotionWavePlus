#include "Renderer.h"

#include "Waveform.h"
#include "audio/AudioData.h"
#include "raylib.h"

#include <cstring>

void Renderer::draw(AudioData *audio) {
    float local[AudioData::kVisualSamples];
    int size;
    {
        // Copy under the lock and draw outside it, so the audio thread waits as little as
        // possible.
        std::lock_guard<std::mutex> lock(audio->audio_mutex);
        size = audio->sample_count;
        std::memcpy(local, audio->audio_samples, size * sizeof(float));
    }

    const float width = static_cast<float>(GetScreenWidth());
    const float height = static_cast<float>(GetScreenHeight());
    const std::vector<Point> points = waveformPoints(local, size, width, height, height * 0.28f);
    for (std::size_t i = 1; i < points.size(); ++i) {
        DrawLineEx({points[i - 1].x, points[i - 1].y}, {points[i].x, points[i].y}, 2.0f, ORANGE);
    }
}
