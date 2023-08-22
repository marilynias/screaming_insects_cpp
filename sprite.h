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

    void add_group(Group<Insect*> *group)
    {
        groups.push_back(group);
    }

    void add_group(Group<Food*> *group)
    {
        
        groups.push_back(group);
    }

    auto getGroups()
    {
        return groups;
    }

    // Vals
    // The X and Y offsets of the dot
    Vector2<float> position;

    int radius;
    Vector2<float> move_direction;

protected:
    virtual void move(){};

    // Vals
    // The move_direction of the dot

    // Maximum axis move_direction of the dot
    int DOT_VEL = 5;

    LTexture image;

    std::vector<void *> groups;
};

#endif