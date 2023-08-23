/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, standard IO, and strings
// #include "vals.h"
#include "funcs.h"
// #include "group.h"
// #include "sprite.h"
#include "insect.h"
#include "classes.h"

#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>

int main(int argc, char *args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            Uint64 frame_time = SDL_GetTicks();
            Uint64 end = 0;
            float elapsed=0;
            SDL_Rect dest = {0, 0, 20, 20};
            SDL_Texture *texture, *text;
            // The dot that will be moving around on the screen
            Group<Insect *> dots;
            Group<Food*> foods;
            // Insect dots[100];

            foods.add(new Food(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, food_rad, GREEN));
            foods.add(new Food(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 4, food_rad, BLUE));
            // foods.add(new Food(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 4, food_rad, YELLOW));
            foods.add(new Food(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, food_rad, RED));

            for (int i = 0; i < num_insects; i++)
            {
                // Insect *dot = new Insect();
                dots.add(new Insect(foods));
            }

            // While application is running
            while (!quit)
            {
                Uint64 start = SDL_GetPerformanceCounter();
                

                handle_events();
                
                // Clear screen to grey                
                SDL_SetRenderDrawColor(gRenderer, 0x55, 0x55, 0x55, 0xff);
                SDL_RenderClear(gRenderer);

                // prepare different color for lines
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

                dots.update();
                foods.update();

                for (auto dot : dots)
                {
                    dot->shout();
                }
                for (auto dot : dots)
                {
                    dot->handle_recieved_shouts();
                }

                dots.draw();
                foods.draw();

                //fps counter
                frame_time = SDL_GetTicks() - frame_time;
                float fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
                // SDL_Color foreground = {0, 0, 0};
                // SDL_Color foreground = {0, 0, 0};
                // SDL_Surface *text_surf = TTF_RenderText(Sans, std::to_string(end).c_str(), {0, 0, 0}, {255, 255, 255});
                // text = SDL_CreateTextureFromSurface(gRenderer, text_surf);
                // SDL_RenderCopy(gRenderer, text, NULL, &dest);

                // Update screen
                SDL_RenderPresent(gRenderer);
                end = SDL_GetPerformanceCounter();
                elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
                // float waitfor = floor(1000.f / 120.f - elapsed);
                SDL_Delay(std::max(floor(1000.f / target_framerate - elapsed), 0.f));
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}
