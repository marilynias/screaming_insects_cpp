#ifndef GROUP_H
#define GROUP_H

#include <type_traits>
#include <vector>
#include <map>
#include <algorithm>

using std::vector;

class Sprite;

bool circles_collide(float x1, float y1, float r1, float x2, float y2, float r2);

template<typename T>
class Group : vector<T>
{
    
public:
    // vector<Sprite*> items;
    // Group() : vector<Sprite *>();
    // static_assert(std::is_base_of<Sprite, T>::value, "T must inherit from list");
    vector<T> spriteCollide(Sprite *sprite, int r1=-1, int r2=-1);
    std::map<T, Sprite *> groupCollide(Group collideGrp, int r1 = -1, int r2 = -1);

    // void push_back();

    void add(T sprite)
    {
        if (!contains(sprite))
        {
            sprite->add_group(this);
            vector<T>::push_back(sprite);
        }
    };

    bool contains(T sprite)
    {
        return std::find(vector<T>::begin(), vector<T>::end(), sprite) != vector<T> ::end();
    };
    // auto a = vector<T>::at(1);

    T getNext(T &sprite);

    T at(int i){return vector<T>::at(i);};
    typename vector<T>::iterator begin() { return vector<T>::begin(); };
    typename vector<T>::iterator end() { return vector<T>::end(); };
    int size() { return vector<T>::size(); }

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