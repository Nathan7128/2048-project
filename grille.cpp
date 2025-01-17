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

Bloc* Grille::getBloc(int i, int j) {
    return m_matBlocs[i][j];
}

void Grille::setBloc(int i, int j, Bloc * bloc) {
    delete m_matBlocs[i][j];
    m_matBlocs[i][j] = bloc;
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

    // On va maintenant déterminer à quelle ligne et quelle colonne correspond la "n_alea"ème case libre de la grille.
    // C'est à dire, nous allons récupérer le pointeur de Bloc actuellement contenu dans la case ou l'on va placer le bloc.
    // Pour cela, nous allons procéder par itération : on traverse une à une les cases de la grille (en procédant ligne par ligne)
    // On détermine à chaque itération la ligne (i) et la colonne (j) de la case, et si la case contient un bloc nul, on incrémente un compteur de
    // blocs nuls initialisé à 0. Lorsque le compteur de blocs nuls aura atteint la valeur de "n_alea", on aura donc atteint la case libre souhaitée,
    // et on connaitra la ligne et la colonne de cette case.
    // Pour déterminer i, nous prenons la division entière du compteur de blocs parcourus "comptBlocs" par la taille de la grille.
    // Pour déterminer j, nous prenons le reste de la division du compteur de blocs parcourus "comptBlocs" par la taille de la grille.
    int comptBlocsNuls = 0, comptBlocs = 0, i, j;
    Bloc* bloc_temp;
    while (comptBlocsNuls < n_alea) {
        i = comptBlocs/m_tailleGrille;
        j = comptBlocs%m_tailleGrille;
        bloc_temp = getBloc(i, j);
        if (bloc_temp->getType() == 1) {
            comptBlocsNuls++;
        }
        comptBlocs++;
    }

    // La variable bloc_temp est donc le pointeur de Bloc situé dans la case ou l'on veut placer le bloc.
    int x = bloc_temp->getX(), y = bloc_temp->getY();
    BlocNumerote * new_bloc;
    new_bloc = new BlocNumerote(x, y, valeurBloc, m_tailleBlocs);
    setBloc(i, j, new_bloc);
    m_nbBlocs++;
}

void Grille::initialiserGrille() {
    int x, y;
    BlocNul * bloc_nul;
    for (int i = 0; i < m_tailleGrille; i++) {
        for (int j = 0; j < m_tailleGrille; j++) {
            x = i * (m_tailleBlocs + m_epCountour) + m_epCountour;
            y = j * (m_tailleBlocs + m_epCountour) + m_epCountour;
            bloc_nul = new BlocNul(x, y, m_tailleBlocs);
            setBloc(i, j, bloc_nul);
        }
    }
    nouveauBlocNum();
    nouveauBlocNum();
}

void Grille::deplacerBloc(int i_old, int j_old, int i_new, int j_new) {
    Bloc * bloc_depl = getBloc(i_old, j_old), * bloc_temp = getBloc(i_new, j_new);
    BlocNul * new_bloc_nul;
    int x_old = bloc_depl->getX(), y_old = bloc_depl->getY();
    int x_new = bloc_temp->getX(), y_new = bloc_temp->getY();

    new_bloc_nul = new BlocNul(x_old, y_old, m_tailleBlocs);
    setBloc(i_old, j_old, new_bloc_nul);

    bloc_depl->setX(x_new);
    bloc_depl->setY(y_new);
    setBloc(i_new, j_new, bloc_depl);
}

void Grille::fusionnerBlocs(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus) {
    BlocNumerote * bloc_depl = getBloc(i_bloc_depl, j_bloc_depl), * bloc_fus = getBloc(i_bloc_fus, j_bloc_fus);
    BlocNul * bloc_nul = new BlocNul(bloc_depl->getX(), bloc_depl->getY(), m_tailleBlocs);
    BlocNumerote * new_bloc = new BlocNumerote(bloc_fus->getX(), bloc_fus->getY(), 2 * bloc_fus->getValeur(), m_tailleBlocs);
    setBloc(i_bloc_depl, j_bloc_depl, bloc_nul);
    setBloc(i_bloc_fus, j_bloc_fus, new_bloc);
    m_nbBlocs--;
}

void Grille::deplacerDroite(int i, int j) {
    int j_new = j;
    BlocNumerote * bloc = getBloc(i, j);

    while (j_new + 1 < m_tailleGrille && getBloc(i, j_new + 1)->getType() == 1) {
        j_new++;
    }

    // Cas ou il y a que des cases vides à droite du bloc, et on peut donc le déplacer jusqu'au bord de la grille
    if (j_new + 1 >= m_tailleGrille) {
        deplacerBloc(i, j, i, j_new);
    }

    // Cas ou le bloc est bloqué par un autre bloc numéroté
    // Il n'y a pas besoin de vérifier que le bloc est bloqué par un autre bloc numéroté car on à vérifier avec le if précédent si il n'y avait que
    // des cases libres à droite du bloc. S'il n'y a pas que des cases libres, cela signifie donc qu'il y a un bloc numéroté
    else {
        BlocNumerote * bloc_droite = getBloc(i, j_new + 1);
        if (bloc_droite->getValeur() == bloc->getValeur()) {
            fusionnerBlocs(i, j, i, j_new + 1);
        }
        // Cas ou le bloc à droite du bloc initial possède une valeur différente, et il y'a au moins une case libre entre ces 2 blocs
        // S'il ces deux blocs sont cotes à cotes (s'il n'y a pas de case libre entre les deux), il n'y a aucun déplacement à effectuer
        else if (j != j_new) {
            deplacerBloc(i, j, i, j_new);
        }
    }
}

void Grille::deplacerGauche(int i, int j) {
    int j_new = j;
    BlocNumerote * bloc = getBloc(i, j);

    while (j_new - 1 >= 0 && getBloc(i, j_new - 1)->getType() == 1) {
        j_new--;
    }

    if (j_new - 1 < 0) {
        deplacerBloc(i, j, i, j_new);
    }

    else {
        BlocNumerote * bloc_gauche = getBloc(i, j_new - 1);
        if (bloc_gauche->getValeur() == bloc->getValeur()) {
            fusionnerBlocs(i, j, i, j_new - 1);
        }
        else if (j != j_new) {
            deplacerBloc(i, j, i, j_new);
        }
    }
}

void Grille::deplacerHaut(int i, int j) {
    int i_new = i;
    BlocNumerote * bloc = getBloc(i, j);

    while (i_new - 1 >= 0 && getBloc(i_new - 1, j)->getType() == 1) {
        i_new--;
    }

    if (i_new - 1 < 0) {
        deplacerBloc(i, j, i_new, j);
    }

    else {
        BlocNumerote * bloc_haut = getBloc(i_new - 1, j);
        if (bloc_haut->getValeur() == bloc->getValeur()) {
            fusionnerBlocs(i, j, i_new - 1, j);
        }
        else if (i != i_new) {
            deplacerBloc(i, j, i_new, j);
        }
    }
}

void Grille::deplacerBas(int i, int j) {
    int i_new = i;
    BlocNumerote * bloc = getBloc(i, j);

    while (i_new + 1 < m_tailleGrille && getBloc(i_new + 1, j)->getType() == 1) {
        i_new++;
    }

    if (i_new + 1 >= m_tailleGrille) {
        deplacerBloc(i, j, i_new, j);
    }

    else {
        BlocNumerote * bloc_bas = getBloc(i_new + 1, j);
        if (bloc_bas->getValeur() == bloc->getValeur()) {
            fusionnerBlocs(i, j, i_new + 1, j);
        }
        else if (i != i_new) {
            deplacerBloc(i, j, i_new, j);
        }
    }
}

void Grille::deplacerBlocs(char direction) {
    int i, j;
    switch (direction) {
        // Direction droite
    case 'd' :
        for (i = 0; i < m_tailleGrille; i++) {
            for (j = m_tailleGrille - 2; j >= 0; j--) {
                deplacerDroite(i, j);
            }
        }
        // Direction gauche
    case 'g' :
        for (i = 0; i < m_tailleGrille; i++) {
            for (j = 1; j < m_tailleGrille; j++) {
                deplacerGauche(i, j);
            }
        }
        // Direction haut
    case 'h' :
        for (i = 1; i < m_tailleGrille; i++) {
            for (j = 0; j < m_tailleGrille; j++) {
                deplacerHaut(i, j);
            }
        }
        // Direction bas
    case 'b' :
        for (i = m_tailleGrille - 2; i >= 0; i--) {
            for (j = 0; j < m_tailleGrille; j++) {
                deplacerBas(i, j);
            }
        }
    }
}

int Grille::estFinie() {
    int finie = 0, compt_directions = 0, i, j;
    char directions[] = {'d', 'g', 'h', 'b'}, direction;
    Bloc * bloc_temp;
    while (finie == 0 && compt_directions < 4) {
        direction = directions[compt_directions];
        switch (direction) {
            // Direction droite
        case 'd' :
            i = 0;
            j = m_tailleGrille - 2;
            while (i < m_tailleGrille && finie == 0) {
                while (j >= 0 && finie == 0) {
                    bloc_temp = getBloc(i, j);
                    deplacerDroite(i, j);
                    j--;
                }
                i++;
            }
            // Direction gauche
        case 'g' :
            for (i = 0; i < m_tailleGrille; i++) {
                for (j = 1; j < m_tailleGrille; j++) {
                    deplacerGauche(i, j);
                }
            }
            // Direction haut
        case 'h' :
            for (i = 1; i < m_tailleGrille; i++) {
                for (j = 0; j < m_tailleGrille; j++) {
                    deplacerHaut(i, j);
                }
            }
            // Direction bas
        case 'b' :
            for (i = m_tailleGrille - 2; i >= 0; i--) {
                for (j = 0; j < m_tailleGrille; j++) {
                    deplacerBas(i, j);
                }
            }
        }
    }
}





