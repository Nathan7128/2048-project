#include "blocnul.h"



BlocNul::BlocNul() {
    m_couleur = "#dbdada";
    m_type = 1;
}

void BlocNul::dessiner(QPainter *p, int x, int y) {
    p->setPen(QPen(QColor("#7c7c7c"), s_epCrayon));
    p->drawRect(x, y, s_tailleBloc, s_tailleBloc);
    p->fillRect(x + s_epCrayon, y + s_epCrayon, s_tailleBloc - s_epCrayon, s_tailleBloc - s_epCrayon, QBrush(m_couleur));
}
