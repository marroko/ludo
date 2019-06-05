#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <random>
#include <chrono>

struct Dice {

    Dice() = default;
    int roll();
};

#endif // DICE_H
