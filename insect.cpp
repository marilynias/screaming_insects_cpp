#include "insect.h"
#include "sprite.h"
#include "vals.h"
#include "classes.h"
#include "group.h"
#include "Vector2.hpp"
#include <algorithm>

// forward declaration
// class Sprite;




// The dot that will move around on the screen
Insect::Insect(Group<Food *> &foodGrp,
               int x,
               int y,
               int radius) : Sprite(x, y, radius)
{
    food_group = &foodGrp;
    target = food_group->at(random()%food_group->size());

    for (auto i : foodGrp)
    {
        targets.insert(std::pair<Food*, int>(i, 1000));
    }
    
}

Insect::Insect(Group<Food *> &foodGrp) : Insect(foodGrp, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 2)
{
}

void Insect::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        std::printf("mouse %i pressed\n", e.button.button);
        std::printf("clicks: %i \n", e.button.clicks);
        std::printf("state: %i \n", e.button.state);
        std::printf("x: %i \n", e.button.x);
        std::printf("y: %i \n", e.button.y);
    }
    else if (e.type == SDL_MOUSEMOTION && e.motion.state == 1)
    {
        position.x = e.motion.x - image.getWidth() / 2;
        position.y = e.motion.y - image.getHeight() / 2;

        std::printf("state: %i \n", e.motion.state);
        std::printf("x: %i \n", e.motion.x);
        std::printf("y: %i \n", e.motion.y);
        // e.motion.
    }
}

void Insect::update()
{
    move_direction.rotate(drift);

    // Move the dot in the direction with the speed of DOT_VEL
    move();
    check_oob();
    check_col_food();
}

void Insect::move()
{
    position += (move_direction * DOT_VEL);
    for (auto &[key, value] : targets)
    {
        value+=DOT_VEL;
    }
}

void Insect::check_col_food()
{
    // for (auto &&cSprite : food_group->groupCollide(*(this->getGroups()[0]), 0, 0))
    for (auto *sprite : food_group->spriteCollide(this, -1, -1))
    {
        move_direction.x = -move_direction.x;
        move_direction.y = -move_direction.y;
        // printf("collision: (%i,%i)\n",
        //        (int)this->position.x,
        //        (int)this->position.y);
        if (sprite == target)
        {
            // std::cout << "Hit my Target!!\n";
            targets[target] = 0;
            target = food_group->getNext(target);
            image.setColor(target->color);
            _do_shout = true;
        }
    }
}

void Insect::check_oob()
{
    // If the dot went too far to the left or right
    if ((position.x < 0) || (position.x + image.getWidth() > SCREEN_WIDTH))
    {
        // Move back
        move_direction.x = -move_direction.x;
        drift = (rand() / RAND_MAX - .5) / 100;
    }

    // If the dot went too far up or down
    if ((position.y < 0) || (position.y + image.getHeight() > SCREEN_HEIGHT))
    {
        // Move back
        move_direction.y = -move_direction.y;
        drift = (rand() / RAND_MAX - .5) / 100;
    }
}

void Insect::shout()
{
    if(_do_shout)
    {
        Group<Insect*> *grp = groups[0];
        auto collided = grp->spriteCollide(this, shout_distance, 0);
        for (auto insect : collided)
        {
            // if (insect->target == target)
            // {
                Targets copy;
                int i = 0;
                for (auto &[key, value] : targets)
                {
                    // if you have many targets only shout to a few of them
                    if (collided.size() < 20 || random() % (collided.size()/5) == 0)
                    {
                        copy[key] = value + shout_distance;
                    }
                    i++;
                }
                insect->recieve_shout(copy, position);
            // }
        }
        _do_shout = false;
    }
}

void Insect::recieve_shout(Targets rTargets, Vector2<float> rDirection)
{
    for (auto &[key, value] : rTargets)
    {
        if (value < _targets_buffer[key])
        {
            _targets_buffer[key] = value;
            if (key == target){_moveto_buffer = rDirection;}
        }
    }
}

void Insect::handle_recieved_shouts()
{
    for (auto &[key, value] : _targets_buffer)
    {
        if(value < targets[key])
        {
            targets[key] = value;
            _do_shout = true;
        }
        if ((_moveto_buffer.x != 0 || _moveto_buffer.y != 0))
        {
            move_direction = (_moveto_buffer - position).normalized();
            SDL_RenderDrawLine(gRenderer, position.x, position.y, _moveto_buffer.x, _moveto_buffer.y);
        }
    }

    //reset buffers
    _targets_buffer = targets + DOT_VEL;
    _moveto_buffer.x = _moveto_buffer.y = 0;
}