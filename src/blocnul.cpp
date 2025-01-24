#include "blocnul.h"



BlocNul::BlocNul(Coordonnees coord, int taille_bloc):Bloc(coord, taille_bloc) {
    m_couleur = QColor("#cdc1b4");
    m_type = 1;
}

void BlocNul::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();
    p->fillRect(x, y, m_tailleBloc, m_tailleBloc, QBrush(m_couleur));
}
