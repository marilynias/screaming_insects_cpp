#include "vals.h"
#include "classes.h"



// values to tinker (insect related)
const int num_insects = 400;
const int shout_distance = 40;
const int limit_shouts_when_above = 40;
// make sure its always smaller then limit_shouts_when_above
const int num_shouted_to_when_limited = limit_shouts_when_above;
const int food_rad = 15;

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
const Color YELLOW = {r : 255, g : 255, b : 0};

bool quit = false;
float target_framerate = 32.;

LTexture gDotTexture;

// TTF_Font *Sans = TTF_OpenFont("Sans.ttf", 24);