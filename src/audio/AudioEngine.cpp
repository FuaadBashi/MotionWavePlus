#define MINIAUDIO_IMPLEMENTATION
#include "../../include/miniaudio.h"
#include "AudioData.h"
#include <iostream> 



void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    AudioData* audio = (AudioData*)pDevice->pUserData;
    float temp[4096 * 2]; // max possible frames * channels

    ma_decoder_read_pcm_frames(&audio->decoder, temp, frameCount, NULL);
    memcpy(pOutput, temp, frameCount * sizeof(float) * pDevice->playback.channels);

    ma_uint32 sample_count = frameCount * pDevice->playback.channels;
    {
        std::lock_guard<std::mutex> lock(audio->audio_mutex);
        
        memcpy(audio->audio_samples, temp, std::min(sample_count, (ma_uint32)4096) * sizeof(float));
        audio->sample_count = std::min(sample_count, (ma_uint32)4096);
    }
    std::cout << "frameCount=" << frameCount << " sample_count=" << audio->sample_count << "\n";
}

static ma_device s_device;

bool initAudio(AudioData* audio_data, const char* file) {
    ma_decoder_config decoder_config = ma_decoder_config_init(ma_format_f32, 2, 44100);
    if (ma_decoder_init_file(file, &decoder_config, &audio_data->decoder) != MA_SUCCESS) {
        std::cout << "Failed to load audio file\n";
        return false;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_f32;
    config.playback.channels = 2;
    config.sampleRate        = 44100;
    config.dataCallback      = data_callback;
    config.pUserData         = audio_data;

    if (ma_device_init(NULL, &config, &s_device) != MA_SUCCESS) {
        std::cout << "Failed to init audio device\n";
        return false;
    }

    ma_device_start(&s_device);
    return true;
}
void cleanupAudio() {
    ma_device_stop(&s_device);
    ma_device_uninit(&s_device);
}