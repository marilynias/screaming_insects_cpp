#ifndef VALS_H
#define VALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "texture.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

typedef std::array<Uint8, 3> Color;

struct Colors
{
    Color black = {0, 0, 0};
    Color white = {255, 255, 255};
    Color red = {255, 0, 0};
    Color green = {0, 255, 0};
    Color blue = {0, 0, 255};
    Color yellow = {255, 255, 0};
    std::vector<Color> all_colors;
    Color random();
} extern colors;

// Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// values to tinker (insect related)
extern int num_insects;
extern int shout_distance;
extern int limit_shouts_when_above;
extern int num_shouted_to_when_limited;
extern int food_rad;
extern int food_spawn_rad;
extern int num_food;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;

extern LTexture gDotTexture;

extern TTF_Font *Sans;

// Main loop flag
extern bool quit;

extern float target_framerate;

#endif