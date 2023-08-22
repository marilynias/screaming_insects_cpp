// #include "../Vector2.h"
#include "classes.h"
#include "vals.h"
#include "group.h"
#include "sprite.h"



#include <stdio.h>
#include <vector>
#include <map>


Food::Food(int x, int y, int radius, Color color) : Sprite(x, y, radius)
{
    image.setColor(color);
    this-> color = color;
};

void Food::update()
{
    
    
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
