#ifndef VALS_H
#define VALS_H

#include <SDL.h>
#include "texture.h"

class Color;

// Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;

extern const Color BLACK;
extern const Color WHITE;
extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;

extern LTexture gDotTexture;

#endif