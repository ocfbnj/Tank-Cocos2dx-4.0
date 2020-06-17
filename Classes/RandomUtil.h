#pragma once

#include <random>

class RandomUtil {
public:
    static int random(int a, int b) {
        static std::random_device r;
        static std::default_random_engine e(r());
        std::uniform_int_distribution<int> dist(a, b);

        return dist(e);
    }
};