#pragma once
#include "AudioData.h"

bool initAudio(AudioData* audio_data, const char* file);
void cleanupAudio();