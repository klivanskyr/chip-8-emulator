#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <optional>
#include "Player.hpp"

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Window {
public:
    size_t width;
    size_t height;
    std::vector<Pixel> pixels;
    std::string map_encoding;
    size_t num_tiles_x;
    size_t num_tiles_y;
    size_t tile_width;
    size_t tile_height;


    Window(size_t w, size_t h, Pixel initialColor = {255, 0, 0});

    std::optional<Pixel> getPixel(size_t x, size_t y);
    void setPixel(size_t x, size_t y, Pixel color);
    std::optional<std::vector<Pixel>> getColumn(size_t x);
    std::optional<std::vector<Pixel>> getRow(size_t y);
    void import_map(const std::string map_encoding, size_t num_tiles_x, size_t num_tiles_y);
    void draw_player(Player& player);
    void draw_rectangle(size_t x1, size_t y1, size_t x2, size_t y2, Pixel color);
};

#endif
