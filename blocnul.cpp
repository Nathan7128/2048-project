#include "blocnul.h"



BlocNul::BlocNul(QColor couleur, int type, int x, int y):Bloc(couleur, type, x, y) {
}

void BlocNul::dessiner(QPainter *p) {
    p->fillRect(m_x, m_y, s_tailleBloc, s_tailleBloc, QBrush(m_couleur));
}
