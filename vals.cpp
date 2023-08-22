#include "vals.h"
#include "classes.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

const Color BLACK = {r : 0, g : 0, b : 0};
const Color WHITE = {r : 255, g : 255, b : 255};
const Color RED = {r:255, g:0, b:0};
const Color GREEN = {r : 0, g : 255, b : 0};
const Color BLUE = {r : 0, g : 0, b : 255};

LTexture gDotTexture;