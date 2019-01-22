#include <algorithm>
#include <vector>
#include <3ds.h>
#include "vec.h"

int main(int argc, char* argv[]) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    gfxSetDoubleBuffering(GFX_BOTTOM, false);

    u8* framebuffer = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

    // you thought it would be 320x240 didn't you
    const int width = 240;
    const int height = 320;
    std::vector<Vec3> fb(width * height);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            fb.at(y * width + x) = Vec3(x / float(width), y / float(height), (x + y) / (float(width) + float(height)));
        }
    }

    size_t j = 0;

    // remember BGR888
    for (size_t i = 0; i < height * (width * 3); i += 3) {
        auto& v = fb[j++];
        framebuffer[i+0] = (u8) (255 * std::max(0.0f, std::min(1.0f, v[0])));
        framebuffer[i+1] = (u8) (255 * std::max(0.0f, std::min(1.0f, v[1])));
        framebuffer[i+2] = (u8) (255 * std::max(0.0f, std::min(1.0f, v[2])));
    }

    while (aptMainLoop()) {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) {
            break;
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
