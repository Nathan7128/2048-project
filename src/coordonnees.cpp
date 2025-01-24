#include "coordonnees.h"

Coordonnees::Coordonnees(int x, int y) {
    m_x = x;
    m_y = y;
}

int Coordonnees::getX() {
    return m_x;
}

int Coordonnees::getY() {
    return m_y;
}

void Coordonnees::setX(int x) {
    m_x = x;
}

void Coordonnees::setY(int y) {
    m_y = y;
}
