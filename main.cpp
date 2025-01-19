#include "mainwindow.h"
#include <time.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    Grille * grille = new Grille(0, 0, 120, 4);
    w.setGrille(grille);
    grille->initialiserGrille();
    w.show();
    return a.exec();
}
