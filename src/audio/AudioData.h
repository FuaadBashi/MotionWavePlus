#pragma once

#include "miniaudio.h"

#include <atomic>
#include <mutex>

// State shared between the miniaudio callback thread and the render loop.
struct AudioData {
    static constexpr int kVisualSamples = 4096;

    // Latest interleaved stereo samples played, copied for the renderer.
    float audio_samples[kVisualSamples] = {};
    int sample_count = 0;
    std::mutex audio_mutex;

    ma_decoder decoder{};
    std::atomic<bool> finished{false};
};
