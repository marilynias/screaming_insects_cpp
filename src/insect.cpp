#include "insect.h"
#include "sprite.h"
#include "vals.h"
#include "classes.h"
#include "group.h"
#include "funcs.h"
#include "Vector2.hpp"
#include <algorithm>

using namespace std;
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
    image.setColor(target->color);
    set_drift();
    speed = float(rand()) / float(RAND_MAX) + 3.f;

    for (auto i : foodGrp)
    {
        targets.insert(pair<Food*, int>(i, 1000));
    }
    
}

Insect::Insect(Group<Food *> &foodGrp) : Insect(foodGrp, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 2)
{
}

void Insect::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        printf("mouse %i pressed\n", e.button.button);
        printf("clicks: %i \n", e.button.clicks);
        printf("state: %i \n", e.button.state);
        printf("x: %i \n", e.button.x);
        printf("y: %i \n", e.button.y);
    }
    else if (e.type == SDL_MOUSEMOTION && e.motion.state == 1)
    {
        position.x = e.motion.x - image.getWidth() / 2;
        position.y = e.motion.y - image.getHeight() / 2;

        printf("state: %i \n", e.motion.state);
        printf("x: %i \n", e.motion.x);
        printf("y: %i \n", e.motion.y);
        // e.motion.
    }
}

void Insect::update()
{
    move_direction.rotate(drift);
    Sprite::move();
    

    for (auto &[key, value] : targets)
    {
        value += speed;
    }
    check_col_food();
}



void Insect::check_col_food()
{
    // for (auto &&cSprite : food_group->groupCollide(*(this->getGroups()[0]), 0, 0))
    for (auto *sprite : food_group->spriteCollide(this, -1, -1))
    {
        // if(num_food == 2)
        // {
            move_direction.x = -move_direction.x;
            move_direction.y = -move_direction.y;
        // }
        // else if (abs(move_direction.x) > move_direction.y)
        // {
        //     move_direction.y = -move_direction.y;
        // }
        // else if (abs(move_direction.y) > move_direction.x)
        // {
        //     move_direction.x = -move_direction.x;
        // }

        if (sprite == target)
        {
            // cout << "Hit my Target!!\n";
            targets[target] = 0;
            last_target = target;
            target = food_group->getNext(target);
            image.setColor(target->color);
        }
        _do_shout = true;
    }
}



void Insect::shout()
{
    if(_do_shout)
    {
        Group<Insect*> *grp = groups[0];
        auto collided = grp->spriteCollide(this, shout_distance, 0);
        // auto col_copy = collided;

        // collided = filterVec(collided, [t = this->target](auto &elem){ return elem->target == t; });
        // vector<Insect*> out;
        // copy_if(collided.begin(), collided.end(), back_inserter(out), [t = this->target](auto &elem)
        //              { return elem->target == t; });
        // std::vector<Insect *> tList;
        Targets copy;
        for (auto &[key, value] : targets)
        {
            // if you have many targets only shout to a few of them
            // if (//last_target == insect->target &&
            // (collided.size() < limit_shouts_when_above || random() % (collided.size() / num_shouted_to_when_limited) == 0))
            // {
            // if (std::count(tList.begin(), tList.end(), insect) == 0)
            // {
            //     tList.push_back(insect);
            // }
            copy[key] = value + shout_distance;
            // }
        }

        for (auto insect : collided)
        {
            
            insect->recieve_shout(copy, position);
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
        if (value < targets[key])
        {
            targets[key] = value;
            _do_shout = true;
        }
        if ((_moveto_buffer.x != 0 || _moveto_buffer.y != 0))
        {
            move_direction = (_moveto_buffer - position).normalized();
            // SDL_RenderDrawLine(gRenderer, position.x, position.y, _moveto_buffer.x, _moveto_buffer.y);
        }
    }

    //reset buffers
    _targets_buffer = targets + speed;
    _moveto_buffer.x = _moveto_buffer.y = 0;
}

void Insect::set_drift()
{
    drift = (float(rand()) / float(RAND_MAX) - .5) / 10.;
}