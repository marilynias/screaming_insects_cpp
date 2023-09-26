#ifndef SPRITE_H
#define SPRITE_H

#include "Vector2.hpp"
#include "texture.h"
#include "group.h"
// #include "classes.h"

#include <vector>

class Insect;
class Food;

// enum class Sprites{Insect, Food};

class Sprite
{
public:
    // Functions
    // Initializes the variables
    Sprite(int x, int y, int radius);
    // ~Sprite();

    virtual void draw();
    // Moves the dot
    virtual void update(){};

    virtual void add_group(Group<Insect*> *group){};
    virtual void add_group(Group<Food*> *group){};

    auto getGroups(){return groups;};

    int radius;
    Vector2<float> position;

protected:
    // Vals
    // The X and Y offsets of the dot
    
    Vector2<float> move_direction;
    float speed;

    virtual void move();
    void check_oob();

    // Vals
    // The move_direction of the dot

    

    LTexture image;

    std::vector<void *> groups;
};

#endif