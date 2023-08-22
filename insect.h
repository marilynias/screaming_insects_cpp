#ifndef INSECT_H
#define INSECT_H


#include "sprite.h"
// #include "classes.h"
#include "group.h"
#include "vals.h"

#include <algorithm>


class Food;
// class Sprite;
// The dot that will move around on the screen
class Insect : public Sprite
{
public:
    Insect(Group<Food *> *foodGrp, int x, int y, int radius);

    Insect(Group<Food *> *foodGrp);

    void update();

    void recieve_shout(int d0, int d1, Vector2<float> direction);

    // Takes key presses and adjusts the dot's move_direction
    void handleEvent(SDL_Event &e);

    // rotate drift
    float drift = (rand() / RAND_MAX - .5) / 100;


    // Insect(Group<Food*> *foodGrp) : Sprite(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 0) {
    //     food_group = foodGrp;
    // target = foodGrp->at(0);
    // }
    

private:
    void move();
    void check_col_food();
    void check_oob();
    void shout();

    Group<Food *> *food_group;
    Food *target;

    int distance0=1000;
    int distance1=1000;
    int shout_distance = 20;

    // std::vector<Group<Sprite*>*> groups;
};

#endif