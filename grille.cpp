#include "grille.h"



Grille::Grille(int x, int y, int hauteurGrille, int largeurGrille, int tailleGrille) {
    m_nbBlocs = 0;
    m_x = x;
    m_y = y;
    m_hauteurGrille = hauteurGrille;
    m_largeurGrille = largeurGrille;
    m_tailleGrille = tailleGrille;
    m_epCountour = 3;

    m_matBlocs = new Bloc * *[tailleGrille];
    for (int i = 0; i < tailleGrille; i++) {
        m_matBlocs[i] = new Bloc * [tailleGrille];
    }
}

BlocNumerote* Grille::nouveauBlocNum(int i, int j, int valeur) {
    int x = i * (m_tailleBlocs + m_epCountour) + m_epCountour, y = j * (m_tailleBlocs + m_epCountour) + m_epCountour;
    BlocNumerote * bloc = new BlocNumerote(x, y, valeur, m_tailleBlocs);
    return bloc;
}
