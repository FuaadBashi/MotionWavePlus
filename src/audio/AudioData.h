#pragma once

#include "SampleExchange.h"
#include "miniaudio.h"

#include <atomic>

// State shared between the miniaudio callback thread and the render loop.
struct AudioData {
    // Latest interleaved stereo samples played, handed to the renderer without the audio thread
    // ever waiting for it.
    SampleExchange visual;

    ma_decoder decoder{};
    std::atomic<bool> finished{false};
};
