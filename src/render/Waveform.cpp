#include "Waveform.h"

std::vector<Point> waveformPoints(const float *interleaved, int sample_count, float width,
                                  float height, float amplitude) {
    const int frames = sample_count / 2;
    std::vector<Point> points;
    if (frames < 2) {
        return points;
    }
    points.reserve(frames);
    for (int i = 0; i < frames; ++i) {
        const float mono = (interleaved[2 * i] + interleaved[2 * i + 1]) / 2.0f;
        points.push_back(
            {i / static_cast<float>(frames - 1) * width, height / 2.0f - mono * amplitude});
    }
    return points;
}
