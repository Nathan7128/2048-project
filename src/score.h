#ifndef SCORE_H
#define SCORE_H



#include <QPainter>
#include "coordonnees.h"
#include <QTextEdit>



// Cette classe permet d'implémenter le score d'une partie, qui augmente à chaque fusion de 2 blocs de la grille.
// Le score est affiché dans la fenêtre principale.
// Telle qu'il est implémenté, le dessin du score dans la fenêtre principale est composé d'un rectangle à l'intérieur duquel se trouvent le mot "score" et la valeur du score affichés.
class Score {
    // Attributs protégés
protected :
    Coordonnees m_coord; /* Coordonnées du coin en haut à gauche du score dans la fenêtre principale */
    int m_hauteur; /* Hauteur du score en pixel */
    int m_largeur; /* Largeur du score en pixel */
    int m_score; /* Score de la partie */

    // Méthodes publiques
public:
    Score(Coordonnees coord = Coordonnees(0, 0)); /* Constructeur par défaut */

    void modifierScore(int valeur); /* Modifie le score en lui ajoutant une valeur passée en paramètre */
    void dessiner(QPainter *p); /* Dessine le score dans la fenêtre principale */
};

#endif // SCORE_H
