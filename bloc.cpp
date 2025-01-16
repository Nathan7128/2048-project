#include "bloc.h"



int Bloc::getType() {
    return m_type;
}

Bloc::Bloc(QColor couleur, int type, int x, int y, int tailleBloc) {
    m_couleur = "#ffffff";
    m_type = 0;
    m_x = x;
    m_y = y;
    m_tailleBloc = tailleBloc;
}
