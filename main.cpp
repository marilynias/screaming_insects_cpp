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
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // The dot that will be moving around on the screen
            Group<Insect*> dots;
            Group<Food*> foods;
            // Insect dots[100];

            foods.add(new FoodA());
            foods.add(new FoodB());

            for (int i = 0; i < 2000; i++)
            {
                // Insect *dot = new Insect();
                dots.add(new Insect(&foods));
            }

            // While application is running
            while (!quit)
            {
                Uint64 start = SDL_GetPerformanceCounter();
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } // On keypress change rgb values
                    

                    // Handle input for the dot
                    // dot.handleEvent(e);
                }

                
                // dot.move();
                // dots[0].move();
                    // for (Insect _dot : dots)
                    // {
                    //     // Move the dot
                    //     _dot.move();
                    // }
                    // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0x55, 0x55, 0x55, 0xff);
                SDL_RenderClear(gRenderer);

                dots.update();
                foods.update();

                dots.draw();
                foods.draw();

                // Update screen
                SDL_RenderPresent(gRenderer);
                Uint64 end = SDL_GetPerformanceCounter();
                float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
                // float waitfor = floor(1000.f / 120.f - elapsed);
                SDL_Delay(std::max(floor(1000.f / 120.f - elapsed), 0.f));
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}
