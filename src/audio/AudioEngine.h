#pragma once

#include "AudioData.h"

// Opens `file` (WAV, MP3 or FLAC) and starts playback. Returns false, with nothing left to clean
// up, if the file or the audio device can't be opened.
bool initAudio(AudioData *audio_data, const char *file);

// Stops playback and releases the device and decoder. Safe to call only after initAudio succeeded.
void cleanupAudio(AudioData *audio_data);
