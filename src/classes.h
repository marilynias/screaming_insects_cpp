#ifndef CLASSES_H
#define CLASSES_H

#include "sprite.h"
#include "group.h"
#include "vals.h"

struct Targets : public std::map<Food *, int>{
    // add distance to all containing targets
    Targets operator+(const int &right) const;
    // remove distance to all containing targets
    Targets operator-(const int &right) const;
    // add distance to all containing targets
    Targets operator+=(const int &right);
    // remove distance to all containing targets
    Targets operator-=(const int &right);
};


// food the dots will seek
class Food : public Sprite
{
    std::vector<Group<Food *> *> groups;
public:
    // Functions
    // Food() : Sprite(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 20){};
    Food(int x = rand() % SCREEN_WIDTH, int y = rand() % SCREEN_HEIGHT, int radius = 0, SDL_Color color = colors.green); //: Sprite(x, y, radius) {}
    void update();
    SDL_Color color;

    

    // Vars
    // Group dots_seeking_me = Group();
    // Group foods;

    
};

#endif