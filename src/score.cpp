#include "score.h"



Score::Score(Coordonnees coord, int largeur, int hauteur) {
    m_coord = coord;
    m_largeur = largeur;
    m_hauteur = hauteur;
    m_score = 0;
}

void Score::modifierScore(int valeur) {
    m_score += valeur;
}

void Score::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();

    // Affichage du rectangle gris contenant le score
    QRect rect_score(x, y, m_largeur, m_hauteur);
    p->fillRect(rect_score, QColor("#898080"));

    p->setPen(QPen(QColor("#ffffff")));

    // Pour afficher le texte "score" et la valeur du score "m_valeur", nous allons centrer ces deux éléments horizontalement, mais afficher le texte
    // en haut du rectangle et la valeur en bas.
    // Pour ce faire, nous allons créer 2 rectangles à l'intérieur du rectangle principal "rect_score", et afficher le texte et la valeur au centre de
    // ces 2 rectangles.

    // Affichage du texte "score"
    int hauteur_rect_texte = m_hauteur/6, y_rect_texte = y + m_hauteur/6;
    QRect rect_texte(x, y_rect_texte, m_largeur, hauteur_rect_texte);

    p->setFont(QFont("Arial", hauteur_rect_texte*0.7, QFont::Bold));
    p->drawText(rect_texte, Qt::AlignHCenter, "SCORE");

    // Affichage de la valeur du score
    int y_rect_valeur = y_rect_texte + hauteur_rect_texte, hauteur_rect_valeur = m_hauteur - y_rect_valeur + y;
    QRect rect_valeur(x, y_rect_valeur, m_largeur, hauteur_rect_valeur);

    // Définition de la police d'écriture de la valeur du score
    // En effet, il faut réduire la taille de la police en fonction du log10 de la valeur du score (du nombre de chiffre dans la valeur)
    int log_valeur = log10(m_score), taille_police;
    switch (log_valeur) {
    case 1:
        taille_police = hauteur_rect_valeur*0.5;
        break;
    case 2:
        taille_police = hauteur_rect_valeur*0.45;
        break;
    case 3:
        taille_police = hauteur_rect_valeur*0.4;
        break;
    case 4:
        taille_police = hauteur_rect_valeur*0.35;
        break;
    case 5:
        taille_police = hauteur_rect_valeur*0.3;
        break;
    default :
        taille_police = hauteur_rect_valeur*0.55;
    }

    p->setFont(QFont("Arial", taille_police, QFont::Bold));
    p->drawText(rect_valeur, Qt::AlignCenter, QString::number(m_score));
}
