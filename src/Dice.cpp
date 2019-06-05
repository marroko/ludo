#include "..\headers\Dice.h"

int Dice::roll() {

    std::default_random_engine randomNumber;
    randomNumber.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distr(1, 6); // define the range

    return distr(randomNumber);
}
