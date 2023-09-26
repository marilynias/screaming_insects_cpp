#include "texture.h"
#include "group.h"
#include "classes.h"

#include <vector>
#include <map>


void handle_events();

bool init();

bool loadMedia();

void close();

// random float between 0-1
float rand1();

template <typename T, typename Pred>
auto filterVec(const std::vector<T> &vec, Pred p);

auto get_config();

void place_food(Group<Food *> *foodGrp, int n, int rad);

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius);

SDL_Color pop_random_color(Colors *clrs);