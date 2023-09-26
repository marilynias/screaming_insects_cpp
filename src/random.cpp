#include "random.h"
#include <random>

int Random::rand_range(int end)
{
    return rand() % abs(end);
}

int Random::rand_range(int start, int end)
{
    return rand_range(end-start)+start;
}



Random::Random()
{
    std::srand(12341);
}

template<typename T>
T Random::rand_choice(std::vector<T> &iter)
{
    return &iter.at(rand_range(iter.size()));
}

template<typename T, typename J>
std::pair<T,J>* Random::rand_choice(std::map<T,J> &iter)
{
    int len = iter.size();
    // T[len] keys;
    // transform(m.begin(), m.end(), back_inserter(keys), RetrieveKey());
}
