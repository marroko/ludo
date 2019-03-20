#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>
#include <iostream>

class Pawn;

class Field {

public:

    Field(QGraphicsPixmapItem *field) : pixmap(field) {}

    Pawn *& getPawn() { return stayingPawn; }
    void setPawn(Pawn *set) { stayingPawn = set; }

    QGraphicsPixmapItem * getPixmap() { return pixmap; }

    void set_Pixmap(QPixmap image) { pixmap->setPixmap(image); }
    void set_Pixmap(QGraphicsPixmapItem *image) {pixmap->setPixmap(image->pixmap());}

    Pawn *stayingPawn = nullptr;

private:

    QGraphicsPixmapItem *pixmap;
};

#endif // FIELD_H
