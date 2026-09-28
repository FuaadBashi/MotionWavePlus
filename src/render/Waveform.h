#pragma once

#include <vector>

struct Point {
    float x;
    float y;
};

// Turns interleaved stereo samples into screen points: channels are averaged to mono, spread
// evenly across `width`, and centred vertically with the given amplitude in pixels. Kept free of
// raylib so it can be unit-tested.
std::vector<Point> waveformPoints(const float *interleaved, int sample_count, float width,
                                  float height, float amplitude);
