#include "sprite.h"
#include "Vector2.hpp"


void Sprite::draw()
{
    // Show the dot
    image.draw(position.x, position.y, radius * 2, radius * 2);
}

Sprite::Sprite(int x = 0, int y = 0, int radius = 0)
{
    image.loadFromFile("media/circle.bmp");

    // Initialize the offsets
    position.x = float(x);
    position.y = float(y);

    // Initialize the move_direction
    move_direction.x = 1.;
    move_direction.y = 0.;
    move_direction.rotate(rand() % 360);

    // if the argument radius is larger then 0(Non-default) set var radius to it, else take the image size(assuming with==height)
    this->radius = radius > 0 ? radius : image.getWidth() / 2;
}
