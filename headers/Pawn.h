#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include <vector>

class Field;

class Pawn {

public:

    typedef std::vector<Field *> Fields;

    Pawn(Field *basePoint, char col, unsigned int start);

    void setField(Field *f) { currentField = f; }
    Field *& getField() { return currentField ; }

    bool move(Fields &fieldsToPlay, Fields &basFin, unsigned int &FINISH);
    char getColour();
    void zero() { passedFields = 0; }

    Field *currentField;

private:

    unsigned int passedFields = 0;
    char colour;
    const unsigned int startID;
};

#endif // PAWN_H
