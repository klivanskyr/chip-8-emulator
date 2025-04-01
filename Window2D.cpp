#include "Window2D.hpp"
#include <fstream>
#include <optional>
#include <iostream>

Window2D::Window2D(size_t w, size_t h, Pixel initialColor) : width(w), height(h), pixels(w * h), tile_width(12), tile_height(12),
      map_encoding(std::string(12 * 12, ' ')) {
    for (size_t i = 0; i < width * height; ++i) {
        pixels[i] = initialColor;
    }
}

// Sets pixel if its within bounds
void Window2D::setPixel(size_t x, size_t y, Pixel color) {
    if (x < width && y < height) {
        pixels[y * width + x] = color;
    }
}

// Gets pixel at (x,y). Optional return Pixel or nullopt
std::optional<Pixel> Window2D::getPixel(size_t x, size_t y) {
    if (x < width && y < height && x >= 0 && y >= 0) {
        return pixels[y * width + x];
    }

    return std::nullopt;
}

// std::optional<std::vector<Pixel>> Window::getRow(size_t y) {
//     if (y >= height || y < 0) return std::nullopt;
//     return std::vector<Pixel>(pixels.begin() + y * width, pixels.begin() + (y + 1) * width);
// }

// std::optional<std::vector<Pixel>> Window::getColumn(size_t x) {
//     if (x < 0 || x >= width) return std::nullopt;
//     std::vector<Pixel> column;
//     for (size_t y = 0; y < height; ++y) {
//         column.push_back(pixels[y * width + x]);
//     }
//     return column;
// }

void Window2D::draw_rectangle(size_t x1, size_t y1, size_t x2, size_t y2, Pixel color) {
    for (size_t i = x1; i < x2; i++) {
        for (size_t j = y1; j < y2; j++) {
            setPixel(i, j, color);
        }
    }
}

// Player is a 3 by 3 square where the middle is (x, y)
void Window2D::draw_player(Player& player) {
    // Top row
    setPixel(tile_width*player.x - 1, tile_height*player.y + 1, {0, 127, 127});
    setPixel(tile_width*player.x, tile_height*player.y + 1, {0, 127, 127});
    setPixel(tile_width*player.x + 1, tile_height*player.y + 1, {0, 127, 127});
    // Middle row
    setPixel(tile_width*player.x - 1, tile_height*player.y, {0, 127, 127});
    setPixel(tile_width*player.x, tile_height*player.y, {0, 127, 127});
    setPixel(tile_width*player.x + 1, tile_height*player.y, {0, 127, 127});
    // Bottom row
    setPixel(tile_width*player.x - 1, tile_height*player.y - 1, {0, 127, 127});
    setPixel(tile_width*player.x, tile_height*player.y - 1, {0, 127, 127});
    setPixel(tile_width*player.x + 1, tile_height*player.y - 1, {0, 127, 127});
}

void Window2D::import_map(const std::string map_encoding, size_t num_tiles_x, size_t num_tiles_y) {
    size_t tile_w = width / num_tiles_x;
    size_t tile_h = height / num_tiles_y;

    this->num_tiles_x = num_tiles_x;
    this->num_tiles_y = num_tiles_y;
    this->tile_width = tile_w;
    this->tile_height = tile_h;
    this->map_encoding = map_encoding;

    for (size_t j = 0; j < num_tiles_y; j++) {
        for (size_t i = 0; i < num_tiles_x; i++) {
            if (map_encoding[j * num_tiles_x + i] == '0') {
                draw_rectangle(
                    i * tile_w,
                    j * tile_h,
                    (i + 1) * tile_w,
                    (j + 1) * tile_h,
                    {0, 0, 0}
                );
            }
        }
    }
}