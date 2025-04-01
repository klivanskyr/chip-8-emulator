#include <vector>
#include <optional>
#include <iostream>
#include <fstream>
#include <cstdint>

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
    
    Window(size_t w, size_t h, Pixel initalColor = {255, 0, 0}) : width(w), height(h), pixels(w * h) {
        for (size_t i = 0; i < width * height; ++i) {
            pixels[i] = initalColor;
        }
    }
    
    // Sets pixel if its within bounds
    void setPixel(size_t x, size_t y, Pixel color) {
        if (x < width && y < height) {
            pixels[y * width + x] = color;
        }
    }

    // Gets pixel at (x,y). Optional return Pixel or nullopt
    std::optional<Pixel> getPixel(size_t x, size_t y) {
        if (x < width && y < height && x >= 0 && y >= 0) {
            return pixels[y * width + x];
        }

        return std::nullopt;
    }

    std::optional<std::vector<Pixel>> getRow(size_t y) {
        if (y >= height || y < 0) return std::nullopt;
        return std::vector<Pixel>(pixels.begin() + y * width, pixels.begin() + (y + 1) * width);
    }

    std::optional<std::vector<Pixel>> getColumn(size_t x) {
        if (x < 0 || x >= width) return std::nullopt;
        std::vector<Pixel> column;
        for (size_t y = 0; y < height; ++y) {
            column.push_back(pixels[y * width + x]);
        }
        return column;
    }

    void draw_rectangle(size_t x1, size_t y1, size_t x2, size_t y2, Pixel color) {
        for (size_t i = x1; i < x2; i++) {
            for (size_t j = y1; j < y2; j++) {
                setPixel(i, j, color);
            }
        }
    }

    void import_map(const std::string map_encoding, size_t map_width, size_t map_height) {
        size_t rect_w = width / map_width;
        size_t rect_h = height / map_height;

        for (size_t j = 0; j < map_height; j++) {
            for (size_t i = 0; i < map_width; i++) {
                if (map_encoding[j * map_width + i] == '0') {
                    draw_rectangle(
                        i * rect_w,
                        j * rect_h,
                        (i + 1) * rect_w,
                        (j + 1) * rect_h,
                        {255, 255, 255}
                    );
                }
            }
        }
    }
};

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


    save_ppm_image("test.ppm", window);

    return 0;
}