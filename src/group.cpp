#include "group.h"

#include "sprite.h"
#include "classes.h"
#include "insect.h"

#include <vector>
#include <map>
#include <algorithm>

using std::map, std::vector;

bool circles_collide(float x1, float y1, float r1, float x2, float y2, float r2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2);
}

template <class T>
vector<T>
Group<T>::spriteCollide(Sprite *sprite, int r1, int r2)
{
    vector<T> collisions;
    
    r2 = r2 >= 0 ? r2 : sprite->radius;
    // Vector2<float> p2 = *sprite->position;
    for (T item : *this)
    {
        r1 = r1 >= 0 ? r1 : item->radius;
        // Vector2<float> p1 = item -> position;

        if (item != sprite && circles_collide(item->position.x + item->radius,
                                              item->position.y + item->radius,
                                              r1,
                                              sprite->position.x + sprite->radius,
                                              sprite->position.y + sprite->radius,
                                              r2))
        {
            collisions.push_back(item);
        }
    }
    return collisions;
};


template <class T>
map<T, Sprite *>
Group<T>::groupCollide(Group<T> collideGrp, int r1, int r2)
{
    map<T, Sprite *> collisions = {};
    for (T item : *this)
    {
        r1 = r1 >= 0 ? r1 : item->radius;
        for (auto item2 : collideGrp)
        {
            
            // Sprite c1 =* item;
            if (item != item2) // && collisions.find(item2) != iterator)
            {
                // Vector2<float> p1 = item->get_position();
                // Vector2<float> p2 = item2->get_position();
                r2 = r2 >= 0 ? r2 : item2->radius;
                auto col = circles_collide(item->position.x + item->radius,
                                           item->position.y + item->radius,
                                           r1,
                                           item2->position.x + item2->radius,
                                           item2->position.y + item2->radius,
                                           r2);
                if (col && (collisions.count(item2) == 0 or collisions[item2] != item))
                {
                    collisions.insert({item, item2});
                    
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
    auto testback = vector<T>::back();
    auto testfront = vector<T>::front();
    if (sprite == vector<T>::back())
    {
        ret = vector<T>::front();
    } else{
        for (int i = 0; i <= vector<T>::size(); i++)
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