#ifndef BOARD_H
#define BOARD_H

#include "Field.h"
#include "Vector.h"
#include "Player.h"
#include "Dice.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QTimer>

class Board : public QGraphicsScene {

    Q_OBJECT

public:

    Board();
    virtual ~Board();

    void draw();
    void drawField(std::vector<Field *> &vec, Vector &current, Vector dir, QString image);
    void play();

    static constexpr int rect_size = 70;

    Vector directions[4] = { Vector (0, -rect_size),   //up
                             Vector (rect_size, 0),    //right
                             Vector (0, rect_size),    //down
                             Vector (-rect_size, 0) }; //left

private:

    std::vector<Field *> fieldsToPlay;
    std::vector<Player *> players;      // players.at(0) == playerBlue
                                        // blue starts the game

    std::vector<Field *> fieldsBlue;    // fields 0-3 basement, fields 4-7 finish
    std::vector<Field *> fieldsRed;
    std::vector<Field *> fieldsYellow;
    std::vector<Field *> fieldsGreen;

    Dice *dice;
    QTimer *timer;
    unsigned int whoseTurn = 0; // 0 - blue, 1 - red, 2 - yellow, 3 - green
};

#endif // BOARD_H
