#include <QApplication>
#include "..\headers\Board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Board *scene = new Board();

    QGraphicsView *view = new QGraphicsView(scene);
    view->resize(1200, 1000);
    view->show();

    scene->draw();
    scene->play();

    return a.exec();
}
