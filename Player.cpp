#include "Player.hpp"
#include "Window2D.hpp" 
#include <cmath> // For sin and cos
#include <optional>
#include <iostream>

Player::Player(size_t x, size_t y, float theta) : x(x), y(y), theta(theta) {}

// Returns the distance from the player to the nearest wall where phi is the angle from where the play is looking (theta)
float Player::find_depth(Window2D& window, float phi) { 
    float depth = 0;
    while (depth < 1000) {
        float point_x = x + depth * cos(theta + phi);
        float point_y = y + depth * sin(theta + phi);

        // check if tile is wall
        int map_x = int(point_x); // truncates to an index in map encoding
        int map_y = int(point_y); // ^

        if (map_x >= window.tile_width || map_y >= window.tile_height) {
            break; // Out of bounds
        }

        // check if tile is wall
        if (window.map_encoding[map_y * window.num_tiles_x + map_x] != ' ') {
            break;
        }

        // draw point on screen
        int screen_x = point_x * window.tile_width;
        int screen_y = point_y * window.tile_height;

        window.setPixel(screen_x, screen_y, {127, 127, 127});

        depth += 0.05;
    
    }

    return depth;
}

std::vector<float> Player::find_pov(Window2D& window, float pov_angle) {
    // draw screen width depth rays, half to the left and half to the right
    std::vector<float> pov(window.width, 0); 
    for (int i = int(-window.width/2); i < int(window.width/2); i++) { // int not size_t so that it can be negative but bad I think
        pov[i + int(window.width/2)] = find_depth(window, pov_angle/int(window.width/2) * i); // also draws the rays
    }

    return pov;
}