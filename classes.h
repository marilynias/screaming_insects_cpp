#ifndef CLASSES_H
#define CLASSES_H

#include "sprite.h"
#include "group.h"
#include "vals.h"

struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
};
// food the dots will seek
class Food : public Sprite
{
public:
    // Functions
    // Food() : Sprite(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 20){};
    Food(int x = rand() % SCREEN_WIDTH, int y = rand() % SCREEN_HEIGHT, int radius = 0, Color color = GREEN); //: Sprite(x, y, radius) {}
    void update();
    Color color;

    // Vars
    // Group dots_seeking_me = Group();
    // Group foods;

    
};

class FoodA: public Food
{
public:
    FoodA() : Food(100, SCREEN_HEIGHT/2, 10, GREEN){};
};

class FoodB : public Food
{
public:
    FoodB() : Food(500, SCREEN_HEIGHT / 2, 10, BLUE){};
};

#endif