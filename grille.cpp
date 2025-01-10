#include "grille.h"



Grille::Grille(int taille) {
    m_taille = taille;
    m_nbBloc = 0;
    m_matBloc = new Bloc * *[taille];

    BlocNul* bloc_nul;
    for (int i = 0; i < taille; i++) {
        m_matBloc[i] = new Bloc * [taille];
        for (int j = 0; j < taille; j++) {
            bloc_nul = new BlocNul();
            m_matBloc[i][j] = bloc_nul;
        }
    }
}
