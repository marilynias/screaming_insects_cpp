#include "vals.h"
#include "classes.h"

// values to tinker (insect related)
int num_insects = 400;
int shout_distance = 40;
int limit_shouts_when_above = 40;
// make sure its always smaller then limit_shouts_when_above
int num_shouted_to_when_limited = limit_shouts_when_above;
int food_rad = 15;
int food_spawn_rad = 200;
int num_food = 2;

// Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

bool quit = false;
float target_framerate = 32.;

LTexture gDotTexture;



Colors colors = {
    .black = {0, 0, 0},
    .white = {255, 255, 255},
    .red = {255, 0, 0},
    .green = {0, 255, 0},
    .blue = {0, 0, 255},
    .yellow = {255, 255, 0},
    .all_colors = {
        {0, 0, 0},
        {255, 255, 255},
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 0}}

};
// {
//     {"black", {0, 0, 0}},
//     {"white", {255, 255, 255}},
//     {"red", {255, 0, 0}},
//     {"green", {0, 255, 0}},
//     {"blue", {0, 0, 255}},
//     {"yellow", {255, 255, 0}}};
// TTF_Font *Sans = TTF_OpenFont("Sans.ttf", 24);