#include "bloc.h"



int Bloc::s_epCrayon = 1;
int Bloc::s_tailleBloc = 15;

Bloc::Bloc() {
    m_type = 0;
    m_couleur = "";
}

QColor Bloc::get_couleur() {
    return m_couleur;
}
