#include "bloc.h"



int Bloc::s_tailleBloc = 30;

Bloc::Bloc(QColor couleur, int type, int x, int y) {
    m_couleur = couleur;
    m_type = type;
    m_x = x;
    m_y = y;
}

void Bloc::setTailleBloc(int tailleBloc) {
    s_tailleBloc = tailleBloc;
}
