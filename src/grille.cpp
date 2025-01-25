#include "grille.h"



Grille::Grille(Coordonnees coord, int tailleGrille, int nbLignesCol) {
    m_nbBlocs = 0;
    m_coord = coord;
    m_tailleGrille = tailleGrille;
    m_nbLignesCol = nbLignesCol;
    m_epContours = tailleGrille / (8 * nbLignesCol + 1);
    m_tailleBlocs = 7 * m_epContours;
    m_tailleGrille = (nbLignesCol + 1)*m_epContours + nbLignesCol*m_tailleBlocs;

    m_matBlocs = new Bloc * *[nbLignesCol];
    for (int i = 0; i < nbLignesCol; i++) {
        m_matBlocs[i] = new Bloc * [nbLignesCol];
        for (int j = 0; j < m_nbLignesCol; j++) {
            m_matBlocs[i][j] = NULL;
        }
    }
}

Grille::Grille(const Grille& g) {
    m_nbBlocs = g.m_nbBlocs;
    m_coord = g.m_coord;
    m_tailleGrille = g.m_tailleGrille;
    m_nbLignesCol = g.m_nbLignesCol;
    m_tailleBlocs = g.m_tailleBlocs;
    m_epContours = g.m_epContours;

    m_matBlocs = new Bloc * *[m_nbLignesCol];
    for (int i = 0; i < m_nbLignesCol; i++) {
        m_matBlocs[i] = new Bloc * [m_nbLignesCol];
        for (int j = 0; j < m_nbLignesCol; j++) {
            *m_matBlocs[i][j] = *g.m_matBlocs[i][j];
        }
    }
}

Grille::~Grille() {
    for (int i = 0; i < m_nbLignesCol; i++) {
        for (int j = 0; j < m_nbLignesCol; j++) {
            delete m_matBlocs[i][j];
        }
        delete[] m_matBlocs[i];
    }
    delete[] m_matBlocs;
}

Grille& Grille::operator=(const Grille& g) {
    if (this != &g) {
        // Destruction du contenu actuel de la grille
        for (int i = 0; i < m_nbLignesCol; i++) {
            for (int j = 0; j < m_nbLignesCol; j++) {
                delete m_matBlocs[i][j];
            }
            delete[] m_matBlocs[i];
        }
        delete[] m_matBlocs;

        // Recopie du contenu de la grille à assigner
        m_nbBlocs = g.m_nbBlocs;
        m_coord = g.m_coord;
        m_tailleGrille = g.m_tailleGrille;
        m_nbLignesCol = g.m_nbLignesCol;
        m_tailleBlocs = g.m_tailleBlocs;
        m_epContours = g.m_epContours;

        m_matBlocs = new Bloc * *[m_nbLignesCol];
        for (int i = 0; i < m_nbLignesCol; i++) {
            m_matBlocs[i] = new Bloc * [m_nbLignesCol];
            for (int j = 0; j < m_nbLignesCol; j++) {
                *m_matBlocs[i][j] = *g.m_matBlocs[i][j];
            }
        }
    }
    return *this;
}

Bloc* Grille::getBloc(int i, int j) {
    return m_matBlocs[i][j];
}

int Grille::getNbBlocs() {
    return m_nbBlocs;
}

int Grille::getNbLignesCol() {
    return m_nbLignesCol;
}

void Grille::setBloc(int i, int j, Bloc * bloc) {
    delete m_matBlocs[i][j];
    m_matBlocs[i][j] = bloc;
}

Coordonnees Grille::convertirCoordBloc(int i, int j) {
    int x_grille = m_coord.getX(), y_grille = m_coord.getY();

    // Convertion de la ligne et de la colonne du bloc
    int x_bloc = j * (m_tailleBlocs + m_epContours) + m_epContours + x_grille;
    int y_bloc = i * (m_tailleBlocs + m_epContours) + m_epContours + y_grille;

    Coordonnees coordBloc(x_bloc, y_bloc);
    return coordBloc;
}

void Grille::nouveauBlocNum() {
    int n_alea = rand()%10, valeurBloc;
    // Déterminer la valeur aléatoire du bloc
    // Pour ce faire, on tire un nombre aléatoire compris entre 0 et 9 inclus, si on tire 0 (proba de 1/10) alors on créé un bloc de valeur 4, sinon 2.
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
    int comptBlocsNuls = 0, comptBlocs = 0, i = 0, j = 0;
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
    Coordonnees coord = convertirCoordBloc(i, j);
    BlocNumerote * new_bloc;
    new_bloc = new BlocNumerote(coord, valeurBloc, m_tailleBlocs);
    setBloc(i, j, new_bloc);
    m_nbBlocs++;
}

void Grille::initialiserGrille() {
    Coordonnees coord;
    BlocNul * bloc_nul;
    for (int i = 0; i < m_nbLignesCol; i++) {
        for (int j = 0; j < m_nbLignesCol; j++) {
            coord = convertirCoordBloc(i, j);
            bloc_nul = new BlocNul(coord, m_tailleBlocs);
            setBloc(i, j, bloc_nul);
        }
    }
    nouveauBlocNum();
    nouveauBlocNum();
}

void Grille::transfererBloc(int i_old, int j_old, int i_new, int j_new) {
    BlocNumerote * bloc_depl = (BlocNumerote*)getBloc(i_old, j_old);
    BlocNul * new_bloc_nul;
    Coordonnees coord_old = convertirCoordBloc(i_old, j_old);
    Coordonnees coord_new = convertirCoordBloc(i_new, j_new);

    new_bloc_nul = new BlocNul(coord_old, m_tailleBlocs);
    m_matBlocs[i_old][j_old] = new_bloc_nul;

    bloc_depl->setCoord(coord_new);
    setBloc(i_new, j_new, bloc_depl);
}

void Grille::fusionnerBlocs(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus) {
    BlocNumerote * bloc_depl = (BlocNumerote*)getBloc(i_bloc_depl, j_bloc_depl), * bloc_fus = (BlocNumerote*)getBloc(i_bloc_fus, j_bloc_fus);
    BlocNul * bloc_nul = new BlocNul(bloc_depl->getCoord(), m_tailleBlocs);
    BlocNumerote * new_bloc = new BlocNumerote(bloc_fus->getCoord(), 2 * bloc_fus->getValeur(), m_tailleBlocs);
    setBloc(i_bloc_depl, j_bloc_depl, bloc_nul);
    setBloc(i_bloc_fus, j_bloc_fus, new_bloc);
    m_nbBlocs--;
}

bool Grille::deplacerBloc(int i, int j, char direction, bool test_finie) {
    int i_new = i, j_new = j, i_fus = i, j_fus = j;
    // bool_bord nous permettra de savoir s'il y a un bloc numéroté entre le bloc à déplacer et le bord (on regarde un des bords en fonction de la
    // direction.
    // est_bloque nous permettra de savoir si le bloc à déplacer est cote à cote (suivant la direction choisie) avec un autre bloc numéroté ou s'il est au bord de la grille.
    // Cela ne veut pas dire que le bloc ne pourra pas être déplacé car il peut être à coté d'un bloc numéroté d'une même valeur et être fusionné
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
        break;
        // Direction gauche
    case 'g' :
        while (j_new - 1 >= 0 && getBloc(i, j_new - 1)->getType() == 1) {
            j_new--;
        }
        j_fus = j_new - 1;
        bool_bord = j_fus < 0;
        break;
        // Direction haut
    case 'h' :
        while (i_new - 1 >= 0 && getBloc(i_new - 1, j)->getType() == 1) {
            i_new--;
        }
        i_fus = i_new - 1;
        bool_bord = i_fus < 0;
        break;
        // Direction bas
    case 'b' :
        while (i_new + 1 < m_nbLignesCol && getBloc(i_new + 1, j)->getType() == 1) {
            i_new++;
        }
        i_fus = i_new + 1;
        bool_bord = i_fus >= m_nbLignesCol;
        break;
    }

    est_bloque = i == i_new && j == j_new;

    // Cas ou il n'y a aucun bloc numéroté entre le bloc à déplacer et le bord (dans la direction ou l'on déplace le bloc)
    // Étant donne qu'on n'essaye jamais de déplacer les blocs au bord de la grille, si bool_bord vaut true alors on déplace forcément le bloc
    // d'au moins une case
    if (bool_bord) {
        if (!test_finie) {
            transfererBloc(i, j, i_new, j_new);
        }
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
            if (!test_finie) {
                fusionnerBlocs(i, j, i_fus, j_fus);
            }
            return true;
        }

        // Cas ou on ne peut pas les fusionner, et il y'a au moins une case libre entre ces 2 blocs
        // S'il ces deux blocs sont cotes à cotes (s'il n'y a pas de case libre entre les deux), il n'y a aucun déplacement à effectuer.
        // C'est ce qu'on vérifie avec la condition du else if
        else if (!est_bloque) {
            if (!test_finie) {
                transfererBloc(i, j, i_new, j_new);
            }
            return true;
        }
    }
    return false;
}

bool Grille::deplacerBlocs(char direction, bool test_finie) {
    int type_bloc;
    int compt_depl = 0; /* Compteur du nombre de déplacement effectuer */
    int i_min = 0, i_max = m_nbLignesCol, i_increm = 1, j_min = 0, j_max = m_nbLignesCol, j_increm = 1; /* Variables utilisées pour la boucle for */

    // Modification des variables en fonction de la direction : on ne déplace pas les blocs dans le même sens suivant la direction choisie */
    switch (direction) {
    case 'd' :
        j_min = m_nbLignesCol - 2;
        j_max = -1;
        j_increm = -1;
        break;
    case 'g' :
        j_min = 1;
        break;
    case 'h' :
        i_min = 1;
        break;
    case 'b' :
        i_min = m_nbLignesCol - 2;
        i_max = -1;
        i_increm = -1;
        break;
    }

    for (int i = i_min; i != i_max; i += i_increm) {
        for (int j = j_min; j != j_max; j += j_increm) {
            type_bloc = getBloc(i, j)->getType();
            if (type_bloc == 2) {
                compt_depl += deplacerBloc(i, j, direction, test_finie);
            }
        }
    }

    if (compt_depl > 0 && !test_finie) {
        nouveauBlocNum();
    }

    return compt_depl > 0;
}

bool Grille::estFinie() {
    // On vérifie si la partie est perdue uniquement dans le cas ou la grille est remplie de blocs numérotés
    if (m_nbBlocs < m_nbLignesCol*m_nbLignesCol) {
        return false;
    }

    // On va parcourir l'ensemble des directions possibles et regarder si on peut déplacer un bloc pour au moins une des directions
    char directions[] = {'d', 'g', 'h', 'b'}, direction;

    for (int i = 0; i < 4; i++) {
        direction = directions[i];
        if (deplacerBlocs(direction, 1)) {
            return false;
        }
    }

    return true;
}

void Grille::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();
    for (int i = 0; i < m_nbLignesCol + 1; i++) {
        // Lorsqu'on trace un rectangle avec fillRect, alors les coordonnées (x, y) qu'on passe en paramètre correspondent au coin en haut à gauche du
        // rectangle, le coin en haut à droite correspond aux coordonneés (x + "largeur rectangle") et le coin en bas à gauche (x, y + "hauteur
        // rectangle")

        // Traçage de la colonne
        p->fillRect(x + i*(m_tailleBlocs + m_epContours), y, m_epContours, m_tailleGrille, QColor("#898080"));

        // Traçage de la ligne
        p->fillRect(x, y + i*(m_tailleBlocs + m_epContours), m_tailleGrille, m_epContours, QColor("#898080"));
    }
}

void Grille::afficherPerdu(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();

    QRect grille(x, y, m_tailleGrille, m_tailleGrille);

    QColor couleur = Qt::gray;
    couleur.setAlphaF(0.7);

    p->fillRect(grille, couleur);

    p->setPen(QPen(QColor("#000000")));
    p->setFont(QFont("Arial", m_tailleGrille/7, QFont::Bold));

    p->drawText(grille, Qt::AlignCenter, "Perdu!");
}





