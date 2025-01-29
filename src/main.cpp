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

    // Instanciation du score de la partie, dépend de la position de la grille
    int largeur_score = 150, hauteur_score = 80;
    int x_score = largeur_fenetre - ((x_grille + taille_grille)/2 + largeur_score/2), y_score = hauteur_fenetre/3;
    Coordonnees coord_score(x_score, y_score);
    Score * score = new Score(coord_score, largeur_score, hauteur_score);
    w.setScore(score);

    // Initialisation de la grille : on la remplit de blocs vides et de 2 blocs numérotés
    grille->initialiserGrille();
    grille->setScore(score);

    // Affichage de la fenêtre
    w.show();

    // Exécution de l'application
    return a.exec();
}
