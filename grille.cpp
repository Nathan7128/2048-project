#include "grille.h"



QColor Grille::s_couleurContours = QColor("#757575");

Grille::Grille(int x, int y, int tailleGrille, int nbLignesCol) {
    m_nbBlocs = 0;
    m_x = x;
    m_y = y;
    m_tailleGrille = tailleGrille;
    m_nbLignesCol = nbLignesCol;
    m_epContours = 3;

    m_matBlocs = new Bloc * *[tailleGrille];
    for (int i = 0; i < tailleGrille; i++) {
        m_matBlocs[i] = new Bloc * [tailleGrille];
    }
}

int Grille::getNbBlocs() {
    return m_nbBlocs;
}

int Grille::getNbLignesCol() {
    return m_nbLignesCol;
}

Bloc* Grille::getBloc(int i, int j) {
    return m_matBlocs[i][j];
}

void Grille::setBloc(int i, int j, Bloc * bloc) {
    // delete m_matBlocs[i][j];
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
    // (nombre de cases libres = nombre de blocs nuls dans la grille = m_nbLignesCol**2 - m_nbBlocs)
    // En fonction de ce nombre choisi, nous allons en déduire la ligne et la colonne ou placer le bloc. Ex : si on tire 2, alors on choisira la 2ème
    // case libre de la grille. Pour trier les cases, on les trie par ligne puis par colonne. Ex (pour une grille 4*4 : la 2ème case correspond à la
    // ligne 1 et colonne 2, la 15ème case correspond à la ligne 4 et la colonne 3. (on considère dans cet exemple que la case en haut à gauche
    // correspond à la ligne 1 et la colonne 1, et non la ligne 0 et la colonne 0 (comme dans le cas ou l'on souhaite accéder aux éléments d'un
    // tableau en C++).
    int nbCasesDispo = m_nbLignesCol*m_nbLignesCol - m_nbBlocs;
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
        i = comptBlocs/m_nbLignesCol;
        j = comptBlocs%m_nbLignesCol;
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
    for (int i = 0; i < m_nbLignesCol; i++) {
        for (int j = 0; j < m_nbLignesCol; j++) {
            x = i * (m_tailleBlocs + m_epContours) + m_epContours;
            y = j * (m_tailleBlocs + m_epContours) + m_epContours;
            bloc_nul = new BlocNul(x, y, m_tailleBlocs);
            setBloc(i, j, bloc_nul);
        }
    }
    nouveauBlocNum();
    nouveauBlocNum();
}

void Grille::transfererBloc(int i_old, int j_old, int i_new, int j_new) {
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
    BlocNumerote * bloc_depl = (BlocNumerote*)getBloc(i_bloc_depl, j_bloc_depl), * bloc_fus = (BlocNumerote*)getBloc(i_bloc_fus, j_bloc_fus);
    BlocNul * bloc_nul = new BlocNul(bloc_depl->getX(), bloc_depl->getY(), m_tailleBlocs);
    BlocNumerote * new_bloc = new BlocNumerote(bloc_fus->getX(), bloc_fus->getY(), 2 * bloc_fus->getValeur(), m_tailleBlocs);
    setBloc(i_bloc_depl, j_bloc_depl, bloc_nul);
    setBloc(i_bloc_fus, j_bloc_fus, new_bloc);
    m_nbBlocs--;
}

bool Grille::deplacerBloc(int i, int j, char direction) {
    int i_new = i, j_new = j, i_fus = i, j_fus = j;
    // bool_bord nous permettra de savoir s'il y a un bloc numéroté entre le bloc à déplacer et le bord (on regarde un des bords en fonction de la
    // direction.
    // est_bloque nous permettra de savoir si le bloc à déplacer est cote à cote (suivant la direction choisie) avec un autre bloc numéroté. Cela ne
    // veut pas dire que le bloc ne pourra pas être déplacé car il peut être à coté d'un bloc numéroté d'une même valeur et être fusionné
    bool bool_bord, est_bloque;
    BlocNumerote * bloc_depl = (BlocNumerote*)getBloc(i, j); /* bloc_depl est le bloc à déplacer */
    switch (direction) {
        // Direction droite
    case 'd' :
        while (j_new + 1 < m_nbLignesCol && getBloc(i, j_new + 1)->getType() == 1) {
            j_new++;
        }
        j_fus = j_new + 1;
        bool_bord = j_fus >= m_nbLignesCol;
        // Direction gauche
    case 'g' :
        while (j_new - 1 >= 0 && getBloc(i, j_new - 1)->getType() == 1) {
            j_new--;
        }
        j_fus = j_new - 1;
        bool_bord = j_fus < 0;
        // Direction haut
    case 'h' :
        while (i_new - 1 >= 0 && getBloc(i_new - 1, j)->getType() == 1) {
            i_new--;
        }
        i_fus = i_new - 1;
        bool_bord = i_fus < 0;
        // Direction bas
    case 'b' :
        while (i_new + 1 < m_nbLignesCol && getBloc(i_new + 1, j)->getType() == 1) {
            i_new++;
        }
        i_fus = i_new + 1;
        bool_bord = i_fus >= m_nbLignesCol;
    }

    est_bloque = i != i_new || j != j_new;

    // Cas ou il n'y a aucun bloc numéroté entre le bloc à déplacer et le bord (dans la direction ou l'on déplace le bloc)
    // est_bloque permet de vérifier si on peut déplacer le bloc d'au moins une case dans la grille, c'est à dire dans ce cas si le bloc est sur le
    // bord de la grille ou pas (par rapport à la direction ou l'on souhaite déplacer le bloc)
    if (bool_bord && est_bloque) {
        transfererBloc(i, j, i_new, j_new);
        return true;
    }

    // Cas ou le bloc à déplacer est bloqué par un autre bloc numéroté
    // Il n'y a pas besoin de vérifier que le bloc est bloqué par un autre bloc numéroté car on à vérifier avec le if précédent si il n'y avait que
    // des cases libres entre le bloc à déplacer et le bord. S'il n'y a pas que des cases libres, cela signifie donc qu'il y a un bloc numéroté
    else {
        // On récupère le pointeur vers le bloc numéroté qui bloque le bloc à déplacer
        BlocNumerote * bloc_fus = (BlocNumerote*)getBloc(i_fus, j_fus);

        // Cas ou on peut fusionner le bloc à déplacer avec le bloc qui le bloque
        if (bloc_fus->getValeur() == bloc_depl->getValeur()) {
            fusionnerBlocs(i, j, i_fus, j_fus);
            return true;
        }

        // Cas ou on ne peut pas les fusionner, et il y'a au moins une case libre entre ces 2 blocs
        // S'il ces deux blocs sont cotes à cotes (s'il n'y a pas de case libre entre les deux), il n'y a aucun déplacement à effectuer.
        // C'est ce qu'on vérifie avec la condition du else if
        else if (est_bloque) {
            transfererBloc(i, j, i_new, j_new);
            return true;
        }
    }
    return false;
}

void Grille::deplacerBlocs(char direction) {
    for (int i = 0; i < m_tailleBlocs; i++) {
        for (int j = 0; j < m_tailleBlocs; j++) {
            if (getBloc(i, j)->getType() == 2) {
                deplacerBloc(i, j, direction);
            }
        }
    }
}

bool Grille::estFinie() {
    bool est_depl = false;
    char directions[] = {'d', 'g', 'h', 'b'}, direction;
    int compt_dir = 0, i, j;
    while (!est_depl && compt_dir < 4) {
        direction = directions[compt_dir];
        i = 0;
        j = 0;
        while (!est_depl && i < m_tailleBlocs) {
            while (!est_depl && j < m_tailleBlocs) {
                if (getBloc(i, j)->getType() == 2) {
                    est_depl = deplacerBloc(i, j, direction);
                }
                // else {
                //     throw "erreur car on regarde si la partie est terminée uniquement lorsque le grille est remplie de blocs numérotés.
                // }
                j++;
            }
            i++;
        }
        compt_dir++;
    }
    // On retourne donc l'inverse de est_depl, car ce dernier vaut true si un déplacement a été effectué, or on souhaite retourner true lorsqu'aucun
    // déplacement n'est possible;
    return !est_depl;
}

void Grille::dessiner(QPainter *p) {
    p->setPen(QPen(s_couleurContours, m_epContours));
    // Traçage des contours extérieur (les bords)

    // Bord haut
    p->drawLine(m_x, m_y, m_x + m_tailleGrille, m_y);
    // Bord bas
    p->drawLine(m_x, m_y + m_tailleGrille, m_x + m_tailleGrille, m_y + m_tailleGrille);
    // Bord gauche
    p->drawLine(m_x, m_y, m_x, m_y + m_tailleGrille);
    // Bord droit
    p->drawLine(m_x + m_tailleGrille, m_y, m_x, m_y + m_tailleGrille);

    // Contours intérieur
    for (int i = 0; i < m_nbLignesCol; i++) {
        // Traçage de la colonne
        p->drawLine(m_x + i*(m_tailleBlocs + m_epContours), m_y, m_x + i*(m_tailleBlocs + m_epContours), m_y + m_tailleGrille);

        // Traçage de la ligne
        p->drawLine(m_x, m_y + i*(m_tailleBlocs + m_epContours), m_x + m_tailleGrille, m_y + i*(m_tailleBlocs + m_epContours));
    }
}



