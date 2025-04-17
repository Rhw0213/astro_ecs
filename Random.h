#pragma once
#include <random>

namespace astro 
{
    struct Random 
    {
        static std::random_device rd;
        static std::mt19937 gen;
        static std::uniform_int_distribution<int> randBright;
        static std::uniform_real_distribution<float> randTwinkle;
        static std::uniform_real_distribution<float> randSize;
    };
}
