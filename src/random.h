#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <vector>
#include <map>

class Random
{
    

    int seed;

public:
    Random();
    int rand_range(int start, int end);
    int rand_range(int end);
    template <typename T> T rand_choice(std::vector<T> &iter);
    template <typename T, typename J> std::pair<T,J>* rand_choice(std::map<T,J> &iter);
};
#endif // __RANDOM_H__