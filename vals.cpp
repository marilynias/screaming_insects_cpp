#include "vals.h"
#include "classes.h"

// values to tinker (insect related)
int num_insects = 400;
int shout_distance = 40;
int limit_shouts_when_above = 40;
// make sure its always smaller then limit_shouts_when_above
int num_shouted_to_when_limited = limit_shouts_when_above;
int food_rad = 15;
int num_food = 2

// Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

Color BLACK = {r : 0, g : 0, b : 0};
Color WHITE = {r : 255, g : 255, b : 255};
Color RED = {r:255, g:0, b:0};
Color GREEN = {r : 0, g : 255, b : 0};
Color BLUE = {r : 0, g : 0, b : 255};
Color YELLOW = {r : 255, g : 255, b : 0};

bool quit = false;
float target_framerate = 32.;

LTexture gDotTexture;

// TTF_Font *Sans = TTF_OpenFont("Sans.ttf", 24);