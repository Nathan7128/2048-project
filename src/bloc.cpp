#include "bloc.h"



Bloc::Bloc(Coordonnees coord, int tailleBloc) {
    if (coord.getX() < 0 && coord.getY() < 0) {
        throw ExceptionCoordNeg("Erreur constructeur de bloc : Coordonnees negatives");
    }
    else if (tailleBloc < 0) {
        throw ExceptionTailleObjet("Erreur constructeur de bloc : Taille negative");
    }
    else {
        m_couleur = QColor("#ffffff");
        m_type = 0;
        m_coord = coord;
        m_tailleBloc = tailleBloc;
    }
}

int Bloc::getType() {
    return m_type;
}

Coordonnees Bloc::getCoord() {
    return m_coord;
}

void Bloc::setCoord(Coordonnees coord) {
    if (coord.getX() < 0 && coord.getY() < 0) {
        throw ExceptionCoordNeg("Erreur methode Bloc::setCoord : Coordonnées negatives");
    }
    else {
        m_coord = coord;
    }
}
