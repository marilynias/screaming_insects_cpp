// #include "../Vector2.h"
#include "classes.h"
#include "vals.h"
#include "group.h"
#include "sprite.h"



#include <stdio.h>
#include <vector>
#include <map>

Targets Targets::operator + (const int &right) const
{
    Targets temp(*this);
    temp += right;
    return temp;
};
Targets Targets::operator - (const int &right) const
{
    Targets temp(*this);
    temp -= right;
    return temp;
};

Targets Targets::operator+=(const int &right)
{
    for (auto &[key, value] : *this)
    {
        value += right;
    }
    return *this;
};

Targets Targets::operator-=(const int &right)
{
    for (auto &[key, value] : *this)
    {
        value -= right;
    }
    return *this;
};

Food::Food(int x, int y, int radius, SDL_Color color) : Sprite(x, y, radius)
{
    image.setColor(color);
    this-> color = color;
    speed = .5;
};

void Food::update()
{
    move();
    
}



// FoodA::FoodA(){};
// FoodB::FoodB(){};
// class FoodA: public Food
// {
// public:
//     FoodA() : Food(10, 10, 10, GREEN){};
// };

// class FoodB : public Food
// {
// public:
//     FoodB() : Food(300, 300, 10, BLUE){};
// };
