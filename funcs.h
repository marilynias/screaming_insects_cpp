#include "texture.h"
#include "vector"



void handle_events();

bool init();

bool loadMedia();

void close();

// random float between 0-1
float rand1();

template <typename T, typename Pred>
auto filterVec(const std::vector<T> &vec, Pred p);