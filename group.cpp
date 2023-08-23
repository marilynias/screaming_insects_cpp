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
    Vector2<float> p2 = sprite->get_position();
    for (T item : *this)
    {
        r1 = r1 >= 0 ? r1 : item->radius;
        Vector2<float> p1 = item -> get_position();        

        if (item != sprite && circles_collide(p1.x + item->radius,
                                           p1.y + item->radius,
                                           r1,
                                           p2.x + sprite->radius,
                                           p2.y + sprite->radius,
                                           r2))
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
                Vector2<float> p1 = item->get_position();
                Vector2<float> p2 = item2->get_position();
                r2 = r2 >= 0 ? r2 : item2->radius;
                auto col = circles_collide(p1.x + item->radius,
                                           p1.y + item->radius,
                                           r1,
                                           p2.x + item2->radius,
                                           p2.y + item2->radius,
                                           r2);
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
T Group<T>::getNext(T &sprite){
    T ret;
    auto testback = std::vector<T>::back();
    auto testfront = std::vector<T>::front();
    if (sprite == std::vector<T>::back())
    {
        ret = std::vector<T>::front();
    } else{
        for (int i = 0; i <= std::vector<T>::size(); i++)
        {
            if (this->at(i) == sprite)
            {
                ret = (this->at(i + 1));
                break;
            }
        }
    }
    return ret;
};

template class Group<Food*>;
template class Group<Insect*>;