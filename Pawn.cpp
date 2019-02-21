#include "Pawn.h"

Pawn::Pawn(Field *basePoint, char col, unsigned int start) :

    currentField(basePoint),
    colour(col),
    startID(start) {}

bool Pawn::move(Fields &fieldsToPlay, Fields &basFin, unsigned int &FINISH) {

    passedFields++;

    if(passedFields >= 48) {

        currentField = basFin.at(4+(passedFields-48));

        if(passedFields == FINISH) {
            FINISH--;
//            delete basFin.at(basFin.size()-1);
            basFin.pop_back();
            return true;
        }

    }
    else
        currentField = fieldsToPlay.at( (startID+passedFields)%48);

    return false;
}

char Pawn::getColour() { return colour; }
