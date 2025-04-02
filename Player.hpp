#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstddef> 
#include <vector>

class Window2D;
struct Depth;

class Player {
public:
    size_t x;
    size_t y;
    float theta;

    Player(size_t x, size_t y, float theta = 0);

    float find_depth(Window2D& window, float phi);
    std::vector<Depth> find_pov(Window2D& window, float pov_angle);
};

#endif
