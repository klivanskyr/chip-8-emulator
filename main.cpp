#include <vector>
#include <optional>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <math.h>

#include "Player.hpp"
#include "Window.hpp"

void save_ppm_image(const std::string filename, const Window& window) {
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << window.width << " " << window.height << "\n255\n";
    for (size_t i = 0; i < window.width * window.height; i++) {
        const Pixel pixel = window.pixels[i]; 
        ofs << static_cast<char>(pixel.r) << static_cast<char>(pixel.g) << static_cast<char>(pixel.b);
    }
    ofs.close();
}

int main() {
    const size_t window_width = 512; // Image width
    const size_t window_height = 512; // Image height
    Window window(window_width, window_height, {255, 0, 0}); // Initialize window with red background

    // Create a gradient from red to green
    for (size_t i = 0; i < window_width; i++) {
        for (size_t j = 0; j < window_height; j++) {
            window.setPixel(i, j, {
                uint8_t(255*i/float(window_width)),
                uint8_t(255*j/float(window_height)),
                0   
            });
        }
    }

    // Split the pixels into a 16x16 grid which we can use to draw maps
    const std::string map_encoding =    "0000000000000000"\
                                        "0              0"\
                                        "0              0"\
                                        "0              0"\
                                        "0              0"\
                                        "0         0    0"\
                                        "0        0     0"\
                                        "0       0      0"\
                                        "0      0       0"\
                                        "0     0        0"\
                                        "0    0         0"\
                                        "0              0"\
                                        "0              0"\
                                        "0              0"\
                                        "0              0"\
                                        "0000000000000000";

    window.import_map(map_encoding, 16, 16);

    // Create player
    Player player(3, 3, 0);
    window.draw_player(player);

    player.find_pov(window, M_PI/6);

    save_ppm_image("test.ppm", window);

    return 0;
}