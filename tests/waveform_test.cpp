#include "render/Waveform.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

static int failures = 0;

#define CHECK(condition)                                                                           \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            std::fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #condition);     \
            ++failures;                                                                            \
        }                                                                                          \
    } while (0)

static bool near(float a, float b) {
    return std::fabs(a - b) < 1e-4f;
}

static void stereo_frames_are_averaged_to_one_point_each() {
    const float samples[] = {0.5f, -0.5f, 1.0f, 1.0f, -1.0f, -0.5f};

    auto points = waveformPoints(samples, 6, 200.0f, 100.0f, 40.0f);

    CHECK(points.size() == 3);
    CHECK(near(points[0].y, 50.0f));         // silence sits on the centre line
    CHECK(near(points[1].y, 10.0f));         // full scale rises by the amplitude
    CHECK(near(points[2].y, 50.0f + 30.0f)); // -0.75 falls below it
}

static void points_span_the_full_width_from_edge_to_edge() {
    const float samples[8] = {};

    auto points = waveformPoints(samples, 8, 1280.0f, 720.0f, 100.0f);

    CHECK(near(points.front().x, 0.0f));
    CHECK(near(points.back().x, 1280.0f));
}

static void fewer_than_two_frames_draw_nothing() {
    const float samples[2] = {0.1f, 0.2f};

    CHECK(waveformPoints(samples, 2, 100.0f, 100.0f, 10.0f).empty());
    CHECK(waveformPoints(samples, 0, 100.0f, 100.0f, 10.0f).empty());
}

int main() {
    stereo_frames_are_averaged_to_one_point_each();
    points_span_the_full_width_from_edge_to_edge();
    fewer_than_two_frames_draw_nothing();

    if (failures > 0) {
        std::fprintf(stderr, "%d check(s) failed\n", failures);
        return EXIT_FAILURE;
    }
    std::printf("All tests passed\n");
    return EXIT_SUCCESS;
}
