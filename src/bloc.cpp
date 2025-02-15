#include "bloc.h"

Bloc::Bloc(Coordonnees coord, int tailleBloc) {
    m_couleur = QColor("#ffffff");
    m_type = 0;
    m_coord = coord;
    m_tailleBloc = tailleBloc;
    m_peutFusionner = true; // Initialisé par défaut à true
}

int Bloc::getType() {
    return m_type;
}

Coordonnees Bloc::getCoord() {
    return m_coord;
}

void Bloc::setCoord(Coordonnees coord) {
    m_coord = coord;
}

// Getter pour peutFusionner
bool Bloc::getPeutFusionner() {
    return m_peutFusionner;
}

// Setter pour peutFusionner
void Bloc::setPeutFusionner(bool peutFusionner) {
    m_peutFusionner = peutFusionner;
}
