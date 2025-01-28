#include "score.h"



Score::Score(Coordonnees coord) {
    m_coord = coord;
    m_score = 0;
}

void Score::modifierScore(int valeur) {
    m_score += valeur;
}

void Score::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();

    QRect score(x, y, m_largeur, m_hauteur);
    p->fillRect(score, QColor("#898080"));

    QTextEdit *texte_score = new QTextEdit();
    texte_score->setText("SCORE");
    texte_score->move()
}
