#ifndef PLAYER_H
#define PLAYER_H

#include "Field.h"
#include "Pawn.h"
#include "Dice.h"
#include <QTimer>

class Player {

public:

    typedef std::vector<Player *> Players;
    typedef std::vector<Field *> Fields;

    virtual ~Player();
    Player(Field *start_point, Fields &playerFields, char col, unsigned int p);
    int turn(Dice *dice, Players &players, Fields &fieldsToPlay);
    void checkIfFieldHasPawn(Players &players, Fields &fieldsToPlay);

    unsigned int FINISH = 51;

private:

    Field * const start;
    Fields &baseAndFinish;
    char colour;

    std::vector<Pawn *> pawns;      // pawns.at(0) is playing
    unsigned int finishedPawns = 0;
    bool hasPawnOnField = false;
};

#endif // PLAYER_H
