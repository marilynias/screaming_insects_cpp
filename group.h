#ifndef GROUP_H
#define GROUP_H

#include <type_traits>
#include <vector>
#include <map>
#include <algorithm>

class Sprite;

bool circles_collide(float x1, float y1, float r1, float x2, float y2, float r2);

template<class T>
class Group : std::vector<T>
{
    
public:
    // std::vector<Sprite*> items;
    // Group() : std::vector<Sprite *>();
    // static_assert(std::is_base_of<Sprite, T>::value, "T must inherit from list");
    std::vector<T> spriteCollide(Sprite *sprite, int r1=-1, int r2=-1);
    std::map<T, Sprite *> groupCollide(Group collideGrp, int r1 = -1, int r2 = -1);

    // void push_back();

    void add(T sprite)
    {
        if (!contains(sprite))
        {
            sprite->add_group(this);
            std::vector<T>::push_back(sprite);
        }
    };

    bool contains(T sprite)
    {
        return std::find(std::vector<T>::begin(), std::vector<T>::end(), sprite) != std::vector<T> ::end();
    };
    // auto a = std::vector<T>::at(1);

    T getNext(T sprite);

    T at(int i)
    {
        return std::vector<T>::at(i);
    };

    // T next(T prev)
    // {

    //     for (T i : this)
    //     {
    //         ;
    //     }
        
    // };

    void draw()
    {
        for (auto item : *this)
        {
            item->draw();
        }
    };

    void update()
    {
        for (auto item : *this)
        {
            item->update();
        }
    };
};

#endif