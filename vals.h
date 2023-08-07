#include <SDL.h>

// DEFS
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// rect to draw
SDL_Surface *gPlayer = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;