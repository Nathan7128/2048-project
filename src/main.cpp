#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Initialisation de la graine du générateur de nombres aléatoires
    srand(static_cast<unsigned int>(std::time(nullptr)));

    // Instanciation de l'application et de la fenêtre
    QApplication a(argc, argv);
    MainWindow w;

    // Affichage de la fenêtre
    w.show();

    // Exécution de l'application
    return a.exec();
}
