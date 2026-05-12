#include "Renderer.h"
#include "raylib.h"
#include "audio/AudioData.h"


bool Renderer::init() {
    return true;
}

void Renderer::draw(AudioData *audio) {

    float local[4096];
    int size;
    {
        std::lock_guard<std::mutex> lock(audio->audio_mutex);
        size = audio->sample_count;
        memcpy(local, audio->audio_samples, size * sizeof(float));
    }
    int frames = size / 2;
    for (int i = 1; i < frames; ++i) {
    float mono_prev = (local[(i-1) * 2] + local[(i-1) * 2 + 1]) / 2.0f;
    float mono_curr = (local[i * 2] + local[i * 2 + 1]) / 2.0f;

    Vector2 prev = { (i-1) / (float)(frames-1) * 1280, 360 + mono_prev * 200.0f };
    Vector2 curr = { i     / (float)(frames-1) * 1280, 360 + mono_curr * 200.0f };

    DrawLineV(prev, curr, ORANGE);
    } //this was done with ai cause i was lazy
}

void Renderer::cleanup() {
}