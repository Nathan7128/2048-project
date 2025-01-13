#include "blocnul.h"



BlocNul::BlocNul(int x, int y, int taille_bloc):Bloc(x, y, taille_bloc) {
    m_couleur = "#dbdada";
    m_type = 1;
}

void BlocNul::dessiner(QPainter *p) {
    p->fillRect(m_x, m_y, m_tailleBloc, m_tailleBloc, QBrush(m_couleur));
}
