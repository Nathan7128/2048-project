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

void Grille::nouveauBlocNum() {
    int n_alea = rand()%4, valeurBloc;
    // Déterminer la valeur aléatoire du bloc
    // Pour ce faire, on tire un nombre aléatoire compris entre 0 et 3 inclus, si on tire 0 (proba de 1/4) alors on créé un bloc de valeur 4, sinon 2.
    if (n_alea == 0) {
        valeurBloc = 4;
    }
    else {
        valeurBloc = 2;
    }

    // Choisir aléatoirement la case (ligne et colonne) ou va se trouver ce nouveau bloc
    // On sait grâce à l'attribut "m_nbBlocs" combien il nous reste de case libre dans la grille. On va donc tirer un nombre aléatoire entre 1 et
    // (nombre de cases libres = nombre de blocs nuls dans la grille = m_tailleGrille**2 - m_nbBlocs)
    // En fonction de ce nombre choisi, nous allons en déduire la ligne et la colonne ou placer le bloc. Ex : si on tire 2, alors on choisira la 2ème
    // case libre de la grille. Pour trier les cases, on les trie par ligne puis par colonne. Ex (pour une grille 4*4 : la 2ème case correspond à la
    // ligne 1 et colonne 2, la 15ème case correspond à la ligne 4 et la colonne 3. (on considère dans cet exemple que la case en haut à gauche
    // correspond à la ligne 1 et la colonne 1, et non la ligne 0 et la colonne 0 (comme dans le cas ou l'on souhaite accéder aux éléments d'un
    // tableau en C++).
    int nbCasesDispo = m_tailleGrille*m_tailleGrille - m_nbBlocs;
    n_alea = rand()%nbCasesDispo + 1; /* Nombre aléatoire entre 1 et et le nombre de cases disponibles */

    // On va maintenant déterminer à quelle ligne et quelle colonne correspond la "n_alea"ème case libre de la grille
    // Pour cela, nous allons procéder par itération : on traverse une à une les cases de la grille (en procédant ligne par ligne)
    // On détermine à chaque itération la ligne (i) et la colonne (j) de la case, et si la case contient un bloc nul, on incrémente un compteur de
    // blocs nuls initialisé à 0. Lorsque le compteur de blocs nuls aura atteint la valeur de "n_alea", on aura donc atteint la case libre souhaitée,
    // et on connaitra la ligne et la colonne de cette case.
    // Pour déterminer i, nous prenons la division entière du compteur de blocs parcourus "comptBlocs" par la taille de la grille.
    // Pour déterminer j, nous prenons le reste de la division du compteur de blocs parcourus "comptBlocs" par la taille de la grille.
    int comptBlocsNuls = 0, comptBlocs = 0, i, j;
    while (comptBlocsNuls < n_alea) {
        i = comptBlocs/m_tailleGrille;
        j = comptBlocs%m_tailleGrille;
        if (m_matBlocs[i][j]->getType() == 1) {
            comptBlocsNuls++;
        }
        comptBlocs++;
    }

    // Il ne nous reste plus qu'à convertir la ligne i et la colonne j déduite en coordonnées x et y (en pixel)
    int x = i * (m_tailleBlocs + m_epCountour) + m_epCountour, y = j * (m_tailleBlocs + m_epCountour) + m_epCountour;
    delete m_matBlocs[i][j];
    m_matBlocs[i][j] = new BlocNumerote(x, y, valeurBloc, m_tailleBlocs);
}

void Grille::nouveauBlocNul(int i, int j) {
    // Convertir la ligne et la colonne en coordonnées x et y (en pixel)
    int x = i * (m_tailleBlocs + m_epCountour) + m_epCountour, y = j * (m_tailleBlocs + m_epCountour) + m_epCountour;
    delete m_matBlocs[i][j];
    m_matBlocs[i][j] = new BlocNul(x, y, m_tailleBlocs);
}


