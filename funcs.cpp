#include "funcs.h"
#include "classes.h"
#include "texture.h"
#include "vals.h"

#include <fstream>
#include <string>
#include <math.h>

using std::map, std::string, std::vector, std::cout, std::stoi;

SDL_Event e;

auto get_config()
{
    std::ifstream cFile("config.cfg");
    map<string, string> config;
    if (cFile.is_open())
    {
        string line;

        while (getline(cFile, line))
        {
            // remove whitespaces
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                       line.end());

            // ignore comments or empty lines
            if (line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            config.insert(std::pair<string, string>(name, value));
            cout << name << " " << value << '\n';

            // why cant you switch/case string values???
            if (name == "num_insects")
            {
                num_insects = stoi(value);
            }
            else if (name == "shout_distance")
            {
                shout_distance = stoi(value);
            }
            else if (name == "limit_shouts_when_above")
            {
                limit_shouts_when_above = stoi(value);
            }
            else if (name == "num_shouted_to_when_limited")
            {
                num_shouted_to_when_limited = stoi(value);
            }
            else if (name == "food_rad")
            {
                food_rad = stoi(value);
            }
            else if (name == "SCREEN_WIDTH")
            {
                SCREEN_WIDTH = stoi(value);
            }
            else if (name == "SCREEN_HEIGHT")
            {
                SCREEN_HEIGHT = stoi(value);
            }
            else if (name == "num_food")
            {
                num_food = stoi(value);
            }
            else if (name == "food_spawn_rad")
            {
                food_spawn_rad = stoi(value);
            }
        }
    }
    return config;
}

void handle_events()
{
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        } // On keypress change rgb values
        else if (e.type == SDL_KEYDOWN){
            if (e.key.keysym.sym == SDLK_PLUS || e.key.keysym.sym == SDLK_KP_PLUS)
            {
                target_framerate = std::min(target_framerate*2., 1024.);
                cout << target_framerate << "\n";
            }
            else if (e.key.keysym.sym == SDLK_MINUS || e.key.keysym.sym == SDLK_KP_MINUS)
            {
                target_framerate = std::max(target_framerate / 2., 2.);
                cout << target_framerate << "\n";
            } else{
                cout << e.key.keysym.scancode << "\n";
            }
        }
        
    }
}

bool init()
{
    // Initialization flag
    bool success = true;

    auto config = get_config();
    // extern int num_insects = config.find("num_insects") != config.end() ? std::stoi(config["num_insects"]): 500;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    srand((unsigned)time(NULL));

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load dot texture
    if (!gDotTexture.loadFromFile("circle.bmp"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    return success;
}

void close()
{
    // Free loaded images
    gDotTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void place_food(Group<Food *> *foodGrp, int n, int r)
{
    double min_rad = 2 * M_PI / n;
    Colors clrs = colors;

    for (int i = 0; i<n; i++)
    {
        double t = min_rad*i;
        float x = (r * cos(t)) + (SCREEN_WIDTH / 2) - food_rad;
        float y = (r * sin(t)) + (SCREEN_HEIGHT / 2) - food_rad;
        Color color = pop_random_color(&clrs);
        foodGrp->add(new Food(x, y, food_rad, color));
        // foodGrp.add(new Food(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, food_rad, colors["green"]));
        // foodGrp.add(new Food(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 4, food_rad, colors["blue"]));
    }
    
    // foods.add(new Food(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 4, food_rad, YELLOW));
    // foods.add(new Food(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, food_rad, RED));
}
// void handle_collisions(Group grp1, Group grp2){

// };

// random float between 0-1
float rand1(){
    return float(rand()) / RAND_MAX;
}

template <typename T, typename Pred>
auto filterVec(vector<T> &vec, Pred p)
{
    {
        vector<T> out;
        std::copy_if(vec.begin(), vec.end(), std::back_inserter(out), p);
        return out;
    }
}

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

Color pop_random_color(Colors *clrs)
{
    int rnd = rand() % clrs->all_colors.size();
    Color el = clrs->all_colors[rnd];
    clrs->all_colors.erase(clrs->all_colors.begin() + rnd);
    return el;
}