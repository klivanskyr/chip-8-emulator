#ifndef WINDOW3D_HPP
#define WINDOW3D_HPP

#include <cstdint>
#include <vector>

struct Pixel;

struct Depth {
    float distance; // distance to wall
    float phi; // angle from player theta 
};

class Window3D {
    public: 
        size_t height;
        size_t width;
        std::vector<Pixel> pixels;
        std::vector<Depth> depths;

    Window3D(size_t height, size_t width, std::vector<Depth> depths);
};

#endif