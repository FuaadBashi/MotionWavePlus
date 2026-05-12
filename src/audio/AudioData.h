#pragma once
#include "../../include/miniaudio.h"
#include <mutex>


struct AudioData {
    float audio_samples[4096];
    int sample_count; 
    std::mutex audio_mutex;
    ma_decoder decoder;
};
