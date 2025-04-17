#include "Random.h"
#include "Common.h"

std::random_device astro::Random::rd;
std::mt19937 astro::Random::gen(astro::Random::rd());
std::uniform_int_distribution<int> astro::Random::randBright(100, 255);
std::uniform_real_distribution<float> astro::Random::randTwinkle(0.5f, 2.f);
std::uniform_real_distribution<float> astro::Random::randSize(1.f, 2.f);