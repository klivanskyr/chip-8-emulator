#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstddef> 
#include <vector>

class Window2D;

class Player {
public:
    size_t x;
    size_t y;
    size_t theta;

    Player(size_t x, size_t y, size_t theta = 0);

    float find_depth(Window2D& window, float phi);
    std::vector<float> find_pov(Window2D& window, float pov_angle);
};

#endif
