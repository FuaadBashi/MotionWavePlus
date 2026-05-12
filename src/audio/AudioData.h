#pragma once
#include "../../include/miniaudio.h"
#include <SDL2/SDL.h>
#include <mutex>


struct AudioData {
    Uint8* buf;  // pointer to the audio file in memory
    Uint32 len;   // ttal size of the audio file in bytes
    Uint32 pos;   // Current playback position (g eg a bookmark)
    float audio_samples[4096];
    int sample_count; 
    std::mutex audio_mutex;
    ma_decoder decoder;
};
