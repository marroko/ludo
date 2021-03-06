#include "..\headers\Player.h"
#include <thread>
#include <chrono>
#include <QDebug> // for qInfo() treated as std::cout

constexpr int BREAK = 5; // higher BREAK means lower simulation speed
                           // lower BREAK means higher simulation speed

Player::Player(Field *start_point, Fields &playerFields, char col, unsigned int p) :

    start(start_point),
    baseAndFinish(playerFields),
    colour(col)
{
    for(unsigned int i=0; i<4 ; ++i) {

        Pawn *tmp = new Pawn(baseAndFinish.at(i), this->colour, p);
        pawns.push_back(tmp);
    }
}

Player::~Player() {

    for (auto & i : pawns)
        delete i;
}

int Player::turn(Dice *dice, Players &players, Fields &fieldsToPlay) {

    int result;
    qInfo() << "Player" << colour;

    if(hasPawnOnField) {

        result = dice->roll();
        qInfo() << result;
        pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/border.png"));

        while(result) {

            pawns.at(0)->currentField->setPawn(nullptr);
            bool finito = pawns.at(0)->move(fieldsToPlay, baseAndFinish, FINISH);

            if(result == 1) {

                checkIfFieldHasPawn(players, fieldsToPlay);
                setPawnOnField();
            }
            pawns.at(0)->currentField->setPawn(pawns.at(0));


            if(finito) {

                finishedPawns++;
                setPawnOnField();
                delete pawns.at(0);
                pawns.erase(pawns.begin());
                hasPawnOnField = false;
                result = 1;
            }

            result--;
        }
        if(finishedPawns == 4) { // condition which ends the game

            qInfo() << "PLAYER" << colour << "WINS!!!";
            return 0;
        }
    }
    else {

       int attempts = 3;

       while(attempts) {

           result = dice->roll();
           qInfo() << result;

           if(result == 6) {

               checkIfFieldHasPawn(players, fieldsToPlay);
               hasPawnOnField = true;
               char col = pawns.at(0)->getColour();

               switch(col) {

               case 'b':
                   pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/blue.png"));
                   break;
               case 'r':
                   pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/red.png"));
                   break;
               case 'y':
                   pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/yellow.png"));
                   break;
               case 'g':
                   pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/green.png"));
                   break;
               }
               pawns.at(0)->setField(start);
               start->setPawn(pawns.at(0));
               start->set_Pixmap(baseAndFinish.at(finishedPawns)->getPixmap());

               checkIfFieldHasPawn(players, fieldsToPlay);

               break;
           }

           std::this_thread::sleep_for(std::chrono::milliseconds(BREAK));

           attempts--;
       }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(BREAK));

    return 1; //next player
}

void Player::checkIfFieldHasPawn(Players &players, Fields &fieldsToPlay) {

    if(pawns.at(0)->currentField->stayingPawn) {

       char col = pawns.at(0)->currentField->stayingPawn->getColour();
       switch (col) {

         case 'b':
           players.at(0)->pawns.at(0)->setField(fieldsToPlay.at(0));
           players.at(0)->pawns.at(0)->zero();
           fieldsToPlay.at(0)->setPawn(players.at(0)->pawns.at(0));
           fieldsToPlay.at(0)->set_Pixmap(QPixmap(":/img/bluepawn.png"));
           break;
         case 'r':
           players.at(1)->pawns.at(0)->setField(fieldsToPlay.at(12));
           players.at(1)->pawns.at(0)->zero();
           fieldsToPlay.at(12)->setPawn(players.at(1)->pawns.at(0));
           fieldsToPlay.at(12)->set_Pixmap(QPixmap(":/img/redpawn.png"));
           break;
         case 'y':
           players.at(2)->pawns.at(0)->setField(fieldsToPlay.at(24));
           players.at(2)->pawns.at(0)->zero();
           fieldsToPlay.at(24)->setPawn(players.at(2)->pawns.at(0));
           fieldsToPlay.at(24)->set_Pixmap(QPixmap(":/img/yellowpawn.png"));
           break;
         case 'g':
           players.at(3)->pawns.at(0)->setField(fieldsToPlay.at(36));
           players.at(3)->pawns.at(0)->zero();
           fieldsToPlay.at(36)->setPawn(players.at(3)->pawns.at(0));
           fieldsToPlay.at(36)->set_Pixmap(QPixmap(":/img/greenpawn.png"));
           break;
       }
    }
}

void Player::setPawnOnField() {

    char col = pawns.at(0)->getColour();
    switch (col) {

        case 'b':
            pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/bluepawn.png"));
            break;
        case 'r':
            pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/redpawn.png"));
            break;
        case 'y':
            pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/yellowpawn.png"));
            break;
        case 'g':
            pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/greenpawn.png"));
            break;
    }
}
