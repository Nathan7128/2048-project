#include "score.h"



Score::Score(Coordonnees coord) {
    m_coord = coord;
    m_score = 0;
}

void Score::modifierScore(int valeur) {
    m_score += valeur;
}

void Score::dessiner(QPainter *p) {

}
