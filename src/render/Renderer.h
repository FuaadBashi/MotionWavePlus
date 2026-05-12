#pragma once
#include <GL/glew.h>

struct AudioData;

class Renderer {
public:
    bool init();
    void draw(AudioData *audio_data);
    void cleanup();
};