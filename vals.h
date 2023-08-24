#ifndef VALS_H
#define VALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "texture.h"

class Color;

// Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// values to tinker (insect related)
extern int num_insects;
extern int shout_distance;
extern int limit_shouts_when_above;
extern int num_shouted_to_when_limited;
extern int food_rad;
extern int num_food;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;

extern Color BLACK;
extern Color WHITE;
extern Color RED;
extern Color GREEN;
extern Color BLUE;
extern Color YELLOW;

extern LTexture gDotTexture;

extern TTF_Font *Sans;

// Main loop flag
extern bool quit;

extern float target_framerate;

#endif