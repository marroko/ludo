#include "Player.h"
#include <thread>
#include <chrono>

constexpr int BREAK = 100;

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

    for (unsigned int i=0; i<pawns.size(); ++i)
        delete pawns.at(i);
}

int Player::turn(Dice *dice, Players &players, Fields &fieldsToPlay) {

    int result;
    std::cout << "Player " << colour << " ";

    if(hasPawnOnField) {

        result = dice->roll();
        std::cout << result << '\n';

        while(result) {

            pawns.at(0)->currentField->set_Pixmap(QPixmap(":/img/border.png"));
            pawns.at(0)->currentField->setPawn(nullptr);
            bool finito = pawns.at(0)->move(fieldsToPlay, baseAndFinish, FINISH);

            if(result == 1)
                checkIfFieldHasPawn(players, fieldsToPlay);

            pawns.at(0)->currentField->setPawn(pawns.at(0));

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

            if(finito) {

                finishedPawns++;
                delete pawns.at(0);
                pawns.erase(pawns.begin());
                hasPawnOnField = false;
                result = 1;
            }

            result--;
        }
        if(finishedPawns == 4) { // condition which ends the game
            std::cout << "PLAYER " << colour << " WINS!!!\n";
            return 0;
        }
    }
    else {

       int attempts = 3;

       while(attempts) {

           result = dice->roll();
           std::cout << result << '\n';

           if(result == 6) {

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

           std::this_thread::sleep_for (std::chrono::milliseconds(BREAK));

           attempts--;
       }
    }

    std::this_thread::sleep_for (std::chrono::milliseconds(BREAK));

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
