#include "Board.h"

Board::Board() : dice(new Dice()) {

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

}

Board::~Board() {

    for (unsigned int i=0; i<fieldsToPlay.size(); ++i) {

        delete fieldsToPlay.at(i);
    }

    for (unsigned int i=0; i<fieldsBlue.size(); ++i) {

        delete fieldsBlue.at(i);
        delete fieldsRed.at(i);
        delete fieldsGreen.at(i);
        delete fieldsYellow.at(i);
    }

    for (unsigned int i=0; i<players.size(); ++i) {

        delete players.at(i);
    }

    delete dice;
    delete timer;
}

void Board::draw() {

    Vector current_pos(350, 840);
    int i,j;

    for(i=0; i<4; ++i) { //drawing fields to play

        for(j=0; j<4; ++j)
            drawField(fieldsToPlay, current_pos, directions[i], ":/img/border.png");

        drawField(fieldsToPlay, current_pos, directions[(i+3)%4], ":/img/border.png");
        drawField(fieldsToPlay, current_pos, directions[i], ":/img/border.png");

        for(j=0; j<4; ++j)
            drawField(fieldsToPlay, current_pos, directions[(i+3)%4], ":/img/border.png");

        for(j=0; j<2; ++j)
            drawField(fieldsToPlay, current_pos, directions[i], ":/img/border.png");

    }

    //setting backgrounds of start-fields
    fieldsToPlay.at(0)->set_Pixmap(QPixmap(":/img/bluestart.png"));
    fieldsToPlay.at(12)->set_Pixmap(QPixmap(":/img/redstart.png"));
    fieldsToPlay.at(24)->set_Pixmap(QPixmap(":/img/yellowstart.png"));
    fieldsToPlay.at(36)->set_Pixmap(QPixmap(":/img/greenstart.png"));
    /////////////////////////////////////

    //drawing basement and finish of each player
    current_pos.x = 70;
    current_pos.y = 70;
    for(j=0; j<4; ++j)
        drawField(fieldsRed, current_pos, directions[(j+1)%4], ":/img/redpawn.png");

    current_pos.x = 70;
    current_pos.y = 420;
    for(j=0; j<4; ++j)
        drawField(fieldsRed, current_pos, directions[1], ":/img/redfinish.png");

    Player *playerRed = new Player(fieldsToPlay.at(12), fieldsRed, 'r', 12);
    //red was drawn

    current_pos.x = 700;
    current_pos.y = 70;

    for(j=0; j<4; ++j)
        drawField(fieldsYellow, current_pos, directions[(j+1)%4], ":/img/yellowpawn.png");

    current_pos.x = 420;
    current_pos.y = 70;
    for(j=0; j<4; ++j)
        drawField(fieldsYellow, current_pos, directions[2], ":/img/yellowfinish.png");

    Player *playerYellow = new Player(fieldsToPlay.at(24), fieldsYellow, 'y', 24);
    //yellow was drawn

    current_pos.x = 700;
    current_pos.y = 700;
    for(j=0; j<4; ++j)
        drawField(fieldsGreen, current_pos, directions[(j+1)%4], ":/img/greenpawn.png");

    current_pos.x = 770;
    current_pos.y = 420;
    for(j=0; j<4; ++j)
        drawField(fieldsGreen, current_pos, directions[3], ":/img/greenfinish.png");

    Player *playerGreen = new Player(fieldsToPlay.at(36), fieldsGreen, 'g', 36);
    //green was drawn

    current_pos.x = 70;
    current_pos.y = 700;

    for(j=0; j<4; ++j)
        drawField(fieldsBlue, current_pos, directions[(j+1)%4], ":/img/bluepawn.png");

    current_pos.x = 420;
    current_pos.y = 770;
    for(j=0; j<4; ++j)
        drawField(fieldsBlue, current_pos, directions[0], ":/img/bluefinish.png");

    Player *playerBlue = new Player(fieldsToPlay.at(0), fieldsBlue, 'b', 0);

    players.push_back(playerBlue);
    players.push_back(playerRed);
    players.push_back(playerYellow);
    players.push_back(playerGreen);
    ////////////////////

    this->setBackgroundBrush(Qt::darkCyan);

}

void Board::drawField(std::vector <Field *> &vec, Vector &current, Vector dir, QString image) {

    QPixmap img(image);
    QGraphicsPixmapItem *rect = this->addPixmap(img);
    rect->setPos(current.x, current.y);
    vec.push_back(new Field(rect));

    current.x += dir.x;
    current.y += dir.y;

}

void Board::play() {

    bool playMore = players.at(whoseTurn)->turn(dice, players, fieldsToPlay);

    if(playMore) {

        whoseTurn++;
        if(whoseTurn == 4)
            whoseTurn=0;

        if(!(fieldsToPlay.at(0)->stayingPawn))
            fieldsToPlay.at(0)->set_Pixmap(QPixmap(":/img/bluestart.png"));
        if(!(fieldsToPlay.at(12)->stayingPawn))
            fieldsToPlay.at(12)->set_Pixmap(QPixmap(":/img/redstart.png"));
        if(!(fieldsToPlay.at(24)->stayingPawn))
            fieldsToPlay.at(24)->set_Pixmap(QPixmap(":/img/yellowstart.png"));
        if(!(fieldsToPlay.at(36)->stayingPawn))
            fieldsToPlay.at(36)->set_Pixmap(QPixmap(":/img/greenstart.png"));

        for (unsigned int i=4; i<fieldsBlue.size(); ++i) {

            if(!(fieldsBlue.at(i)->stayingPawn))
                fieldsBlue.at(i)->set_Pixmap(QPixmap(":/img/bluefinish.png"));
        }
        for (unsigned int i=4; i<fieldsRed.size(); ++i) {

            if(!(fieldsRed.at(i)->stayingPawn))
                fieldsRed.at(i)->set_Pixmap(QPixmap(":/img/redfinish.png"));
        }
        for (unsigned int i=4; i<fieldsYellow.size(); ++i) {

            if(!(fieldsYellow.at(i)->stayingPawn))
                fieldsYellow.at(i)->set_Pixmap(QPixmap(":/img/yellowfinish.png"));
        }
        for (unsigned int i=4; i<fieldsGreen.size(); ++i) {

            if(!(fieldsGreen.at(i)->stayingPawn))
                fieldsGreen.at(i)->set_Pixmap(QPixmap(":/img/greenfinish.png"));
        }

        QTimer::singleShot(200, [this] { play(); } );
    }
}
