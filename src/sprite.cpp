#include "sprite.h"
#include "Vector2.hpp"
#include "vals.h"



Sprite::Sprite(int x = 0, int y = 0, int radius = 0)
{
    image.loadFromFile("media/circle.bmp");

    // Initialize the offsets
    position.x = float(x);
    position.y = float(y);

    // Initialize the move_direction
    move_direction.x = 1.;
    move_direction.y = 0.;
    move_direction.rotate((rand() % RAND_MAX) *(2*M_PI));

    // if the argument radius is larger then 0(Non-default) set var radius to it, else take the image size(assuming with==height)
    this->radius = radius > 0 ? radius : image.getWidth() / 2;
}

void Sprite::draw()
{
    // Show the dot
    image.draw(position.x, position.y, radius * 2, radius * 2);
}

void Sprite::move()
{
    position += (move_direction * speed);
    check_oob();
}

void Sprite::check_oob()
{
    // If the dot went too far to the left or right
    if ((position.x < 0) || (position.x + image.getWidth() > SCREEN_WIDTH))
    {
        // Move back
        move_direction.x = -move_direction.x;
    }

    // If the dot went too far up or down
    if ((position.y < 0) || (position.y + image.getHeight() > SCREEN_HEIGHT))
    {
        // Move back
        move_direction.y = -move_direction.y;
    }
}