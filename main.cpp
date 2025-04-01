#include <vector>
#include <optional>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <math.h>

#include "Player.hpp"
#include "Window2D.hpp"
#include "Window3D.hpp"

void save_ppm_image(const std::string filename, const Window2D& window2D, const Window3D& window3D) {
    //assumes both are same height
    std::ofstream ofs(filename, std::ios::binary);

    size_t combined_width = window2D.width + window3D.width;

    ofs << "P6\n" << combined_width << " " << window2D.height << "\n255\n";

    for (size_t y = 0; y < window2D.height; y++) {
        for (size_t x = 0; x < combined_width; x++) {
            Pixel pixel;
            if (x < window2D.width) { // Left side
                pixel = window2D.pixels[y * window2D.width + x];

            } else { // Right side
                size_t x_3D = x - window2D.width; // Shift x for 3D window
                pixel = window3D.pixels[y * window3D.width + x_3D];
            }

            ofs << char(pixel.r) << char(pixel.g) << char(pixel.b);
        }
    }

    ofs.close();
}

int main() {
    const size_t window_width = 512; // Image width
    const size_t window_height = 512; // Image height
    Window2D window2D(window_width, window_height, {255, 255, 255});

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

    window2D.import_map(map_encoding, 16, 16);

    // Create player
    Player player(3, 3, 0);
    window2D.draw_player(player);

    std::vector<float> depths = player.find_pov(window2D, M_PI/6);

    // Draw The 3D view
    Window3D window3D(window_height, window_width, depths);


    save_ppm_image("test.ppm", window2D, window3D);

    return 0;
}