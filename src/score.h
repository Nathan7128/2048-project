#ifndef SCORE_H
#define SCORE_H



#include "QPainter"
#include "coordonnees.h"



// Cette classe permet d'implémenter le score d'une partie, qui augmente à chaque fusion de 2 blocs de la grille.
// Le score est affiché dans la fenêtre principale
class Score {
    // Attributs protégés
protected :
    Coordonnees m_coord; /* Coordonnées du coin en haut à gauche du score dans la fenêtre principale */
    int m_score; /* Score de la partie */

    // Méthodes publiques
public:
    Score(Coordonnees coord = Coordonnees(0, 0)); /* Constructeur par défaut */

    void modifierScore(int valeur); /* Modifie le score en lui ajoutant une valeur passée en paramètre */
    void dessiner(QPainter *p); /* Dessine le score dans la fenêtre principale */
};

#endif // SCORE_H
