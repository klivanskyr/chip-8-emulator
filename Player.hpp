#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstddef> 
#include <vector>

class Window;

class Player {
public:
    size_t x;
    size_t y;
    size_t theta;

    Player(size_t x, size_t y, size_t theta = 0);

    float find_depth(Window& window, float phi);
    std::vector<float> find_pov(Window& window, float pov_angle);
};

#endif
