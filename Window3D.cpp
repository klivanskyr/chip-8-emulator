#include "Window3D.hpp"
#include "Window2D.hpp"
#include <vector>

Window3D::Window3D(size_t w, size_t h, std::vector<float> depths) : width(w), height(h), depths(depths), pixels(w * h, {255, 255, 255}) {
    for (size_t i = 0; i < depths.size(); i++) {
        // Ensure depth is nonzero to avoid division by zero
        if (depths[i] <= 0.01f) continue;

        // How many pixels should the wall be?
        float inverse = 1 / depths[i];
        // what is the ratio of this in terms of height of pixels
        size_t wall_height = size_t(height * inverse);

        size_t top = size_t(height / 2) - size_t(wall_height / 2);
        size_t bottom = size_t(height / 2) + size_t(wall_height / 2);

        // draw the wall centered at midline
        for (size_t j = 0; j < height; j++) {
            if (j >= top && j <= bottom) {
                pixels[j*width + i] = {255, 0, 0};
            }
        }
    };
}