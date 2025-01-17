#include "bloc.h"



Bloc::Bloc(int x, int y, int tailleBloc) {
    m_couleur = "#ffffff";
    m_type = 0;
    m_x = x;
    m_y = y;
    m_tailleBloc = tailleBloc;
}

int Bloc::getType() {
    return m_type;
}

int Bloc::getX() {
    return m_x;
}

int Bloc::getY() {
    return m_y;
}

void Bloc::setX(int x) {
    m_x = x;
}

void Bloc::setY(int y) {
    m_y = y;
}
