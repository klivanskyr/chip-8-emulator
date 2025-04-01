#ifndef WINDOW3D_HPP
#define WINDOW3D_HPP

#include <cstdint>
#include <vector>
#include "Window2D.hpp"

class Window3D {
    public: 
        size_t height;
        size_t width;
        std::vector<Pixel> pixels;
        std::vector<float> depths;

    Window3D(size_t height, size_t width, std::vector<float> depths);
};

#endif