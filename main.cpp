/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Vector2.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Texture wrapper class
class LTexture {
    public:
        // Initializes variables
        LTexture();

        // Deallocates memory
        ~LTexture();

        // Loads image at specified path
        bool loadFromFile(std::string path);

        #if defined(SDL_TTF_MAJOR_VERSION)
            // Creates image from font string
            bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
        #endif

        // Deallocates texture
        void free();

        // Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        // Set blending
        void setBlendMode(SDL_BlendMode blending);

        // Set alpha modulation
        void setAlpha(Uint8 alpha);

        // Renders texture at given point
        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        // Gets image dimensions
        int getWidth();
        int getHeight();

        // Image dimensions
        int mWidth;
        int mHeight;

    private:
        // The actual hardware texture
        SDL_Texture *mTexture;

        
};


// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Scene textures
LTexture gDotTexture;

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    
}

LTexture::~LTexture()
{
    // Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0x00, 0x00));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface != NULL)
    {
        // Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    else
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    // Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    // Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate texture rgb
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    // Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

// The dot that will move around on the screen
class Dot
{
public:
    // The X and Y offsets of the dot
    Vector2<float> position;

    // The move_direction of the dot
    Vector2<float> move_direction;

    // Maximum axis move_direction of the dot
    static const int DOT_VEL = 10;

    // Initializes the variables
    Dot(int x, int y);
    Dot();

    // Takes key presses and adjusts the dot's move_direction
    void handleEvent(SDL_Event &e);

    // Moves the dot
    void move();

    // Shows the dot on the screen
    void render();

    // rotate drift
    int drift = rand() % 3 - 1;

private:
    LTexture image;
};

Dot::Dot(){
    image = gDotTexture;

    // Initialize the offsets
    position.x = float(rand() % SCREEN_WIDTH);
    position.y = float(rand() % SCREEN_HEIGHT);
    

    // Initialize the move_direction
    move_direction.x = 1.;
    move_direction.y = 1.;
}

Dot::Dot(int x, int y)
{
    image = gDotTexture;

    // Initialize the offsets
    position.x = float(x);
    position.y = float(y);

    // Initialize the move_direction
    move_direction.x = 1.;
    move_direction.y = 1.;

    // std::printf("new_pos: %f", position. + move_direction);
}

void Dot::handleEvent(SDL_Event &e)
{
    // If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        // Adjust the move_direction
        // switch (e.key.keysym.sym)
        // {
        // case SDLK_UP:
        //     mVelY -= DOT_VEL;
        //     break;
        // case SDLK_DOWN:
        //     mVelY += DOT_VEL;
        //     break;
        // case SDLK_LEFT:
        //     mVelX -= DOT_VEL;
        //     break;
        // case SDLK_RIGHT:
        //     mVelX += DOT_VEL;
        //     break;
        // }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        // Adjust the move_direction
        // switch (e.key.keysym.sym)
        // {
        // case SDLK_UP:
        //     move_direction.y += DOT_VEL;
        //     break;
        // case SDLK_DOWN:
        //     move_direction.y -= DOT_VEL;
        //     break;
        // case SDLK_LEFT:
        //     move_direction.x += DOT_VEL;
        //     break;
        // case SDLK_RIGHT:
        //     move_direction.x -= DOT_VEL;
        //     break;
        // }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN){
        std::printf( "mouse %i pressed\n", e.button.button);
        std::printf("clicks: %i \n",  e.button.clicks );
        std::printf("state: %i \n", e.button.state);
        std::printf("x: %i \n", e.button.x);
        std::printf("y: %i \n", e.button.y);
    }
    else if (e.type == SDL_MOUSEMOTION && e.motion.state == 1)
    {
        position.x = e.motion.x - image.mWidth / 2;
        position.y = e.motion.y - image.mHeight / 2;

        std::printf("state: %i \n", e.motion.state);
        std::printf("x: %i \n", e.motion.x);
        std::printf("y: %i \n", e.motion.y);
        // e.motion.
    }
}

void Dot::move()
{
    move_direction.rotate(drift);

    // Move the dot in the direction with the speed of DOT_VEL
    position += move_direction * DOT_VEL;

    // If the dot went too far to the left or right
    if ((position.x < 0) || (position.x + image.mWidth > SCREEN_WIDTH))
    {
        // Move back
        move_direction.x = -move_direction.x;
    }


    // If the dot went too far up or down
    if ((position.y < 0) || (position.y + image.mHeight > SCREEN_HEIGHT))
    {
        // Move back
        move_direction.y = -move_direction.y;
    }
}

void Dot::render()
{
    // Show the dot
    image.render(position.x, position.y);
}

bool init()
{
    // Initialization flag
    bool success = true;

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
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
            Dot dots[100];
            // for (int i = 0; i < 10; i++)
            // {
            //     dots[i] = Dot();
            // }

            // printf("dots: ");
            // for (auto dot : dots){
            //     printf("(%i, %i),\n", int(dot.position.x), int(dot.position.y));
            // }
            Dot dot = Dot(0,0);

            // Modulation components
            Uint8 r = 255;
            Uint8 g = 255;
            Uint8 b = 255;

            // While application is running
            while (!quit)
            {
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

                
                dot.move();
                dots[0].move();
                    // for (Dot _dot : dots)
                    // {
                    //     // Move the dot
                    //     _dot.move();
                    // }
                    // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0x55, 0x55, 0x55, 0xff);
                SDL_RenderClear(gRenderer);

                gDotTexture.setColor(r, g, b);
                gDotTexture.render(50,50);

                // Render objects
                // dots.
                // for (Dot _dot: dots){
                //     // Move the dot
                //     _dot.render();
                // }
                dots[0].render();
                dot.render();

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}
