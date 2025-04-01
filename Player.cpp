#include "Player.hpp"
#include "Window.hpp" 
#include <cmath> // For sin and cos
#include <optional>
#include <iostream>

Player::Player(size_t x, size_t y, size_t theta) : x(x), y(y), theta(theta) {}

// Returns the distance from the player to the nearest wall where phi is the angle from where the play is looking (theta)
float Player::find_depth(Window& window, float phi) { 
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

        depth += 0.1;
    
    }

    return depth;
}

std::vector<float> Player::find_pov(Window& window, float pov_angle) {
    // draw 512 depth rays, 256 to the left and 256 to the right
    std::vector<float> pov(512, 0);
    for (int i = -256; i < 256; i++) {
        pov[i + 256] = find_depth(window, theta + (pov_angle/256 * i)); // also draws the rays
    }

    return pov;
}