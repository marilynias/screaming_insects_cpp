#ifndef VALS_H
#define VALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "texture.h"

class Color;

// Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// values to tinker (insect related)
extern const int num_insects;
extern const int shout_distance;
extern const int limit_shouts_when_above;
extern const int num_shouted_to_when_limited;
extern const int food_rad;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;

extern const Color BLACK;
extern const Color WHITE;
extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;
extern const Color YELLOW;

extern LTexture gDotTexture;

extern TTF_Font *Sans;

// Main loop flag
extern bool quit;

extern float target_framerate;

#endif