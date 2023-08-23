#ifndef INSECT_H
#define INSECT_H


#include "sprite.h"
#include "classes.h"
#include "group.h"
#include "vals.h"

#include <algorithm>


class Food;
// class Sprite;
// The dot that will move around on the screen
class Insect : public Sprite
{
private:
    void move();
    void check_col_food();
    void check_oob();
    void set_drift();

    Group<Food *> *food_group;
    Food *target;

    Targets targets;

    Targets _targets_buffer;
    Vector2<float> _moveto_buffer;
    bool _do_shout = false;

    // variable speeds helps against clumping
    const float SPEED = float(rand()) / float(RAND_MAX) + 3;
    

    std::vector<Group<Insect *> *> groups;

public:
    Insect(Group<Food *> &foodGrp, int x, int y, int radius);
    Insect(Group<Food *> &foodGrp);

    // things to do in the main loop
    void update();
    void handle_recieved_shouts();
    void shout();

    void recieve_shout(Targets direction, Vector2<float> position);

    // Takes key presses and adjusts the dot's move_direction
    void handleEvent(SDL_Event &e);

    // rotate drift
    float drift;

    void add_group(Group<Insect *> *group) {groups.push_back(group);}
};

#endif