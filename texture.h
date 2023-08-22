#ifndef TEXTURE_H
#define TEXTURE_H


// #include "classes.h"
// #include "vals.h"

#include <SDL.h>
#include <SDL_image.h>
#include "string"

class Color;

// Texture wrapper class
class LTexture
{
public:
    // Initializes variables
    LTexture();

    // Deallocates memory
    ~LTexture();

    // Loads image at specified path
    bool loadFromFile(std::string path);

    // Deallocates texture
    void free();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(Color color);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Renders texture at given point
    void draw(int x, int y, int w, int h, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Gets image dimensions
    int getWidth();
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};



#endif