#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "AudioEngine.h"

#include <cstring>
#include <iostream>

namespace {

constexpr ma_uint32 kChannels = 2;
constexpr ma_uint32 kSampleRate = 44100;

ma_device s_device;

// Runs on miniaudio's real-time thread, so it must not wait on locks, allocate or print. (It used
// to print on every call.) It does decode here, which reads the file; see the README.
void data_callback(ma_device *device, void *output, const void * /*input*/, ma_uint32 frame_count) {
    auto *audio = static_cast<AudioData *>(device->pUserData);
    auto *out = static_cast<float *>(output);

    // Decode straight into the output buffer. The old fixed-size stack buffer overflowed
    // whenever the device asked for more than 4096 frames.
    ma_uint64 frames_read = 0;
    ma_decoder_read_pcm_frames(&audio->decoder, out, frame_count, &frames_read);
    if (frames_read < frame_count) {
        // Past the end of the file: play silence, not whatever was in the buffer.
        std::memset(out + frames_read * kChannels, 0,
                    (frame_count - frames_read) * kChannels * sizeof(float));
        audio->finished = true;
    }

    // Never waits: if the renderer is mid-copy, this block is simply not drawn.
    audio->visual.tryPublish(out, static_cast<int>(frame_count * kChannels));
}

} // namespace

bool initAudio(AudioData *audio_data, const char *file) {
    ma_decoder_config decoder_config =
        ma_decoder_config_init(ma_format_f32, kChannels, kSampleRate);
    if (ma_decoder_init_file(file, &decoder_config, &audio_data->decoder) != MA_SUCCESS) {
        std::cerr << "Could not open audio file: " << file << "\n";
        return false;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = kChannels;
    config.sampleRate = kSampleRate;
    config.dataCallback = data_callback;
    config.pUserData = audio_data;

    if (ma_device_init(nullptr, &config, &s_device) != MA_SUCCESS ||
        ma_device_start(&s_device) != MA_SUCCESS) {
        std::cerr << "Could not start the audio device\n";
        ma_decoder_uninit(&audio_data->decoder);
        return false;
    }
    return true;
}

void cleanupAudio(AudioData *audio_data) {
    ma_device_uninit(&s_device);             // stops the device first
    ma_decoder_uninit(&audio_data->decoder); // was never released before
}
