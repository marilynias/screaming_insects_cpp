#include "group.h"

#include "sprite.h"
#include "classes.h"
#include "insect.h"

#include <vector>
#include <map>
#include <algorithm>

bool circles_collide(float x1, float y1, float r1, float x2, float y2, float r2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2);
}

template <class T>
std::vector<T>
Group<T>::spriteCollide(Sprite *sprite, int r1, int r2)
{
    std::vector<T> collisions = {};
    
    r2 = r2 >= 0 ? r2 : sprite->radius;
    for (T item : *this)
    {
        r1 = r1 >= 0 ? r1 : item->radius;
        // Sprite c1 =* item;
        if (item != sprite && circles_collide(item->position.x + r1,
                                              item->position.y + r1,
                                              item->radius,
                                              sprite->position.x + r2,
                                              sprite->position.y + r2,
                                              sprite->radius)) // && collisions.find(item2) != iterator)
        {
            collisions.push_back(item);
        }
    }
    return collisions;
};


template <class T>
std::map<T, Sprite *>
Group<T>::groupCollide(Group<T> collideGrp, int r1, int r2)
{
    std::map<T, Sprite *> collisions = {};
    for (T item : *this)
    {
        r1 = r1 >= 0 ? r1 : item->radius;
        for (auto item2 : collideGrp)
        {
            
            // Sprite c1 =* item;
            if (item != item2) // && collisions.find(item2) != iterator)
            {
                
                r2 = r2 >= 0 ? r2 : item2->radius;
                auto col = circles_collide(item->position.x + r1,
                                           item->position.y + r1,
                                           item->radius,
                                           item2->position.x + r2,
                                           item2->position.y + r2,
                                           item2->radius);
                if (col)
                {
                    if (collisions.count(item2) == 0 or collisions[item2] != item)
                    {
                        // printf("collision: (%i,%i), (%i,%i)\n",
                        //        (int)item->position.x,
                        //        (int)item->position.y,
                        //        (int)item2->position.x,
                        //        (int)item2->position.y);
                        // std::cout << "COLLISION\n";
                        collisions.insert({item,
                                           item2});
                    }
                }
            }
            // std::cout << item2 -> position.x << ", " << item -> position.x << "\n";
            // std::cout << &item2 << ", " << &item << "\n";
        }
    }
    return collisions;
};

template <class T>
T Group<T>::getNext(T sprite){
    T ret;
    T back = std::vector<T>::back();
    if (sprite == back)
    {
        ret = std::vector<T>::front();
    } else{
        for (int i = 0; i <= std::vector<T>::size(); i++)
        {
            if (this->at(i) == sprite)
            {
                ret = this->at(i + 1);
                break;
            }
        }
    }
    return ret;
};

template class Group<Food*>;
template class Group<Insect*>;