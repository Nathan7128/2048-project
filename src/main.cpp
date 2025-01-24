#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Initialisation de la graine du générateur de nombres aléatoires
    srand(static_cast<unsigned int>(std::time(nullptr)));

    // Instanciation de l'application et de la fenêtre
    QApplication a(argc, argv);
    MainWindow w;

    // Modification de la taille de la fenêtre
    int hauteur_fenetre = 700, largeur_fenetre = 1200;
    w.resize(largeur_fenetre, hauteur_fenetre);

    // Instanciation de la grille, on la positionne à 10 pixels du bord gauche et centrée par rapport à l'axe vertical
    int taille_grille = 500, nb_LignesCol = 4;
    int x_grille = 10, y_grille = (hauteur_fenetre - taille_grille)/2;
    Coordonnees coord_grille(x_grille, y_grille);
    Grille * grille = new Grille(coord_grille, taille_grille, nb_LignesCol);
    w.setGrille(grille);

    // Initialisation de la grille : on la remplit de blocs vides et de 2 blocs numérotés
    grille->initialiserGrille();

    // Affichage de la fenêtre
    w.show();

    // Exécution de l'application
    return a.exec();
}
