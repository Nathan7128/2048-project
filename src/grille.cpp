#include "grille.h"



Grille::Grille(Coordonnees coord, int taille, int nbLignesCol) {
    m_nbBlocs = 0;
    m_coord = coord;
    m_taille = taille;
    m_nbLignesCol = nbLignesCol;
    m_epContours = taille / (8 * nbLignesCol + 1);
    m_tailleBlocs = 7 * m_epContours;
    m_taille = (nbLignesCol + 1)*m_epContours + nbLignesCol*m_tailleBlocs;

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
    m_taille = g.m_taille;
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
        m_taille = g.m_taille;
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

void Grille::setScore(Score * score) {
    m_score = score;
}

Coordonnees Grille::convertirCoordBloc(int i, int j) {
    int x_grille = m_coord.getX(), y_grille = m_coord.getY();

    // Convertion de la ligne et de la colonne du bloc
    int x_bloc = j * (m_tailleBlocs + m_epContours) + m_epContours + x_grille;
    int y_bloc = i * (m_tailleBlocs + m_epContours) + m_epContours + y_grille;

    Coordonnees coordBloc(x_bloc, y_bloc);
    return coordBloc;
}

#include <QDebug>

void Grille::nouveauBlocNum() {
    qDebug() << "Entrée dans nouveauBlocNum()";
    int n_alea = rand() % 10, valeurBloc;
    // Déterminer la valeur aléatoire du bloc
    // Pour ce faire, on tire un nombre aléatoire compris entre 0 et 9 inclus, si on tire 0 (proba de 1/10) alors on créé un bloc de valeur 4, sinon 2.
    if (n_alea == 0) {
        valeurBloc = 4;
        qDebug() << "n_alea == 0, valeurBloc = 4";
    }
    else {
        valeurBloc = 2;
        qDebug() << "n_alea != 0, valeurBloc = 2";
    }

    // Choisir aléatoirement la case (ligne et colonne) ou va se trouver ce nouveau bloc
    // On sait grâce à l'attribut "m_nbBlocs" combien il nous reste de cases libres dans la grille. On va donc tirer un nombre aléatoire entre 1 et
    // (nombre de cases libres = nombre de blocs nuls dans la grille = m_nbLignesCol**2 - m_nbBlocs)
    // En fonction de ce nombre choisi, nous allons en déduire la ligne et la colonne ou placer le bloc. Ex : si on tire 2, alors on choisira la 2ème
    // case libre de la grille. Pour trier les cases, on les trie par ligne puis par colonne. Ex (pour une grille 4*4 : la 2ème case correspond à la
    // ligne 1 et colonne 2, la 15ème case correspond à la ligne 4 et la colonne 3. (on considère dans cet exemple que la case en haut à gauche
    // correspond à la ligne 1 et la colonne 1, et non la ligne 0 et la colonne 0 (comme dans le cas où l'on souhaite accéder aux éléments d'un
    // tableau en C++).
    int nbCasesDispo = m_nbLignesCol * m_nbLignesCol - m_nbBlocs;
    n_alea = rand() % nbCasesDispo + 1; /* Nombre aléatoire entre 1 et le nombre de cases disponibles */
    qDebug() << "Nombre de cases disponibles:" << nbCasesDispo << ", n_alea:" << n_alea;

    // On va maintenant déterminer à quelle ligne et quelle colonne correspond la "n_alea"ème case libre de la grille.
    // C'est à dire, nous allons récupérer le pointeur de Bloc actuellement contenu dans la case où l'on va placer le bloc.
    // Pour cela, nous allons procéder par itération : on traverse une à une les cases de la grille (en procédant ligne par ligne)
    // On détermine à chaque itération la ligne (i) et la colonne (j) de la case, et si la case contient un bloc nul, on incrémente un compteur de
    // blocs nuls initialisé à 0. Lorsque le compteur de blocs nuls aura atteint la valeur de "n_alea", on aura donc atteint la case libre souhaitée,
    // et on connaîtra la ligne et la colonne de cette case.
    // Pour déterminer i, nous prenons la division entière du compteur de blocs parcourus "comptBlocs" par la taille de la grille.
    // Pour déterminer j, nous prenons le reste de la division du compteur de blocs parcourus "comptBlocs" par la taille de la grille.
    int comptBlocsNuls = 0, comptBlocs = 0, i = 0, j = 0;
    Bloc* bloc_temp;
    while (comptBlocsNuls < n_alea) {
        i = comptBlocs / m_nbLignesCol;
        j = comptBlocs % m_nbLignesCol;
        bloc_temp = getBloc(i, j);
        if (bloc_temp->getType() == 1) {
            comptBlocsNuls++;
            qDebug() << "Bloc nul trouvé à (" << i << "," << j << "), compteur:" << comptBlocsNuls;
        }
        comptBlocs++;
    }
    qDebug() << "Position choisie pour nouveau bloc: ligne" << i << "colonne" << j;

    // La variable bloc_temp est donc le pointeur de Bloc situé dans la case où l'on veut placer le bloc.
    Coordonnees coord = convertirCoordBloc(i, j);
    qDebug() << "Coordonnées du bloc:" << coord.getX() << coord.getY();

    BlocNumerote* new_bloc = new BlocNumerote(coord, valeurBloc, m_tailleBlocs);
    setBloc(i, j, new_bloc);
    m_nbBlocs++;
    qDebug() << "Nouveau bloc numérique créé avec valeur:" << valeurBloc << ", m_nbBlocs maintenant:" << m_nbBlocs;
}


void Grille::nouveauBlocBonus() {
    int n_alea = rand()%12, valeurBloc;
    // Déterminer la valeur aléatoire du bloc bonus
    // Cette valeur est égale au coefficient multiplicateur qui agit lors d'une fusion avec un bloc numéroté.
    // Pour déterminer cette valeur, on tire un nombre aléatoire compris entre 0 et 11 inclus.
    if (n_alea >= 0 && n_alea <= 7) { // Si ce nombre est compris entre 0 et 7 inclus, la valeur du bloc bonus est 2.
        valeurBloc = 2; // Proba de 8/12 = 3/2
    }
    else if (n_alea >= 8 && n_alea <= 10){ // Si ce nombre est compris entre 8 et 10 inclus, la valeur du bloc bonus est 4.
        valeurBloc = 4; // Proba de 3/12 = 1/4
    }
    else{ // Si ce nombre est égal à 11, la valeur du bloc bonus est 8.
        valeurBloc = 8; // Proba de 1/12
    }

    // Choisir aléatoirement la case (ligne et colonne) ou va se trouver ce nouveau bloc
    // On sait grâce à l'attribut "m_nbBlocs" combien il nous reste de case libre dans la grille. On va donc tirer un nombre aléatoire entre 1 et
    // (nombre de cases libres = nombre de blocs nuls dans la grille = m_nbLignesCol**2 - m_nbBlocs)
    // En fonction de ce nombre choisi, nous allons en déduire la ligne et la colonne où placer le bloc. Ex : si on tire 2, alors on choisira la 2ème
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
    BlocBonus * new_bloc;
    new_bloc = new BlocBonus(coord, valeurBloc, m_tailleBlocs);
    setBloc(i, j, new_bloc);
    m_nbBlocs++;
}

void Grille::nouveauBlocMalus() {
    int n_alea = rand()%12, valeurBloc;
    // Déterminer la valeur aléatoire du bloc malus
    // Cette valeur est égale au coefficient multiplicateur qui agit lors d'une fusion avec un bloc numéroté.
    // Pour déterminer cette valeur, on tire un nombre aléatoire compris entre 0 et 11 inclus.
    if (n_alea >= 0 && n_alea <= 7) { // Si ce nombre est compris entre 0 et 7 inclus, la valeur du bloc malus est 2.
        valeurBloc = 2; // Proba de 8/12 = 3/2
    }
    else if (n_alea >= 8 && n_alea <= 10){ // Si ce nombre est compris entre 8 et 10 inclus, la valeur du bloc malus est 4.
        valeurBloc = 4; // Proba de 3/12 = 1/4
    }
    else{ // Si ce nombre est égal à 11, la valeur du bloc  est 8.
        valeurBloc = 8; // Proba de 1/12
    }

    // Choisir aléatoirement la case (ligne et colonne) ou va se trouver ce nouveau bloc
    // On sait grâce à l'attribut "m_nbBlocs" combien il nous reste de case libre dans la grille. On va donc tirer un nombre aléatoire entre 1 et
    // (nombre de cases libres = nombre de blocs nuls dans la grille = m_nbLignesCol**2 - m_nbBlocs)
    // En fonction de ce nombre choisi, nous allons en déduire la ligne et la colonne où placer le bloc. Ex : si on tire 2, alors on choisira la 2ème
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
    BlocMalus * new_bloc;
    new_bloc = new BlocMalus(coord, valeurBloc, m_tailleBlocs);
    setBloc(i, j, new_bloc);
    m_nbBlocs++;
}

void Grille::initialiserGrille() {
    qDebug() << "Initialisation de la grille...";
    Coordonnees coord;
    BlocNul * bloc_nul;
    for (int i = 0; i < m_nbLignesCol; i++) {
        for (int j = 0; j < m_nbLignesCol; j++) {
            coord = convertirCoordBloc(i, j);
            bloc_nul = new BlocNul(coord, m_tailleBlocs);
            setBloc(i, j, bloc_nul);
            qDebug() << "Bloc nul créé à (" << i << "," << j << ") avec coord:" << coord.getX() << coord.getY();
        }
    }
    qDebug() << "Création des deux nouveaux blocs numériques...";
    nouveauBlocNum();
    nouveauBlocNum();
    qDebug() << "Initialisation de la grille terminée.";
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


// Fusionner deux blocs numérotés
void Grille::fusionnerBlocsNumeroteNumerote(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus, char direction) {
    BlocNumerote* bloc_depl = (BlocNumerote*)getBloc(i_bloc_depl, j_bloc_depl);
    BlocNumerote* bloc_fus = (BlocNumerote*)getBloc(i_bloc_fus, j_bloc_fus);

    // Création d'un bloc nul pour remplacer les deux blocs
    BlocNul* bloc_nul = new BlocNul(bloc_fus->getCoord(), m_tailleBlocs);

    // La nouvelle valeur est la somme des deux blocs numérotés
    int nouvelle_valeur = bloc_depl->getValeur() + bloc_fus->getValeur();

    // Création du nouveau bloc numéroté avec la position du bloc déplacé
    BlocNumerote* new_bloc = new BlocNumerote(bloc_depl->getCoord(), nouvelle_valeur, m_tailleBlocs);

    marquerNonFusionnable(i_bloc_depl, j_bloc_depl, direction);


    // Remplacer les blocs dans la grille
    setBloc(i_bloc_depl, j_bloc_depl, new_bloc);
    setBloc(i_bloc_fus, j_bloc_fus, bloc_nul);

    // Mise à jour du score
    m_score->modifierScore(nouvelle_valeur);
    m_nbBlocs--;  // Une fusion libère une case dans la grille
}

void Grille::fusionnerBlocsNumeroteBonus(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus,  char direction) {
    BlocNumerote* bloc_depl = (BlocNumerote*)getBloc(i_bloc_depl, j_bloc_depl);
    BlocBonus* bloc_fus = (BlocBonus*)getBloc(i_bloc_fus, j_bloc_fus);

    // Création d'un bloc nul pour remplacer le bloc bonus
    BlocNul* bloc_nul = new BlocNul(bloc_fus->getCoord(), m_tailleBlocs);

    // La nouvelle valeur est la multiplication de la valeur numérotée par la valeur bonus
    int nouvelle_valeur = bloc_depl->getValeur() * bloc_fus->getValeur();

    // Création du nouveau bloc numéroté avec la position du bloc déplacé
    BlocNumerote* new_bloc = new BlocNumerote(bloc_depl->getCoord(), nouvelle_valeur, m_tailleBlocs);

    marquerNonFusionnable(i_bloc_depl, j_bloc_depl, direction);

    // Remplacer les blocs dans la grille
    setBloc(i_bloc_depl, j_bloc_depl, new_bloc);
    setBloc(i_bloc_fus, j_bloc_fus, bloc_nul);

    // Mise à jour du score
    m_score->modifierScore(nouvelle_valeur);
    m_nbBlocs--;  // Une fusion libère une case dans la grille
}



// Fusionner un bloc bonus et un bloc numéroté (le bonus se déplace sur le numéroté)
void Grille::fusionnerBlocsBonusNumerote(int i_bloc_bonus, int j_bloc_bonus, int i_bloc_numero, int j_bloc_numero,  char direction) {
    BlocBonus* bloc_bonus = (BlocBonus*)getBloc(i_bloc_bonus, j_bloc_bonus);
    BlocNumerote* bloc_numero = (BlocNumerote*)getBloc(i_bloc_numero, j_bloc_numero);

    // Création d'un bloc nul pour remplacer le bloc bonus
    BlocNul* bloc_nul = new BlocNul(bloc_bonus->getCoord(), m_tailleBlocs);

    // La nouvelle valeur est la multiplication de la valeur du numéroté par la valeur du bonus
    int nouvelle_valeur = bloc_bonus->getValeur() * bloc_numero->getValeur();

    // Création du nouveau bloc numéroté à la position du bloc bonus (c'est-à-dire où le bonus se trouve)
    BlocNumerote* new_bloc = new BlocNumerote(bloc_bonus->getCoord(), nouvelle_valeur, m_tailleBlocs);

    marquerNonFusionnable(i_bloc_bonus, j_bloc_bonus, direction);


    // Remplacer les blocs dans la grille : remplacer le bloc bonus par un bloc nul, et mettre le bloc numéroté avec la nouvelle valeur à la position du bonus
    setBloc(i_bloc_bonus, j_bloc_bonus, new_bloc);
    setBloc(i_bloc_numero, j_bloc_numero, bloc_nul);

    // Mise à jour du score
    m_score->modifierScore(nouvelle_valeur);
    m_nbBlocs--;  // Une fusion libère une case dans la grille
}


void Grille::fusionnerBlocsNumeroteMalus(int i_bloc_numero, int j_bloc_numero, int i_bloc_malus, int j_bloc_malus,  char direction) {
    BlocNumerote* bloc_numero = (BlocNumerote*)getBloc(i_bloc_numero, j_bloc_numero);
    BlocMalus* bloc_malus = (BlocMalus*)getBloc(i_bloc_malus, j_bloc_malus);
    // Sauvegarder la valeur initiale du bloc numéroté va nous servir pour calculer la perte de points liée à la fusion avec le bloc malus
    int valeur_initiale = bloc_numero->getValeur();

    // Création d'un bloc nul pour remplacer le bloc malus
    BlocNul* bloc_nul = new BlocNul(bloc_malus->getCoord(), m_tailleBlocs);

    // La nouvelle valeur est divisée par la valeur du malus
    int nouvelle_valeur = bloc_numero->getValeur() / bloc_malus->getValeur();
    if (nouvelle_valeur < 2) {
        nouvelle_valeur = 2;  // Si la divison est strictement inférieure à 2, le bloc a la valeur 2 car c'est le minimum possible dans le jeu
    }

    // Création du nouveau bloc numéroté avec la position du bloc déplacé
    BlocNumerote* new_bloc = new BlocNumerote(bloc_numero->getCoord(), nouvelle_valeur, m_tailleBlocs);

    marquerNonFusionnable(i_bloc_numero, j_bloc_numero, direction);

    // Remplacer les blocs dans la grille
    setBloc(i_bloc_numero, j_bloc_numero, new_bloc);
    setBloc(i_bloc_malus, j_bloc_malus, bloc_nul);

    int perte_points = valeur_initiale - nouvelle_valeur;

    // Mise à jour du score
    if (m_score->getScore() < perte_points){
        m_score->reinitialiserScore();
    }
    else{
        m_score->modifierScore(-perte_points);
    }
    m_nbBlocs--;  // Une fusion libère une case dans la grille
}

void Grille::fusionnerBlocsMalusNumerote(int i_bloc_malus, int j_bloc_malus, int i_bloc_numero, int j_bloc_numero,  char direction) {
    BlocMalus* bloc_malus = (BlocMalus*)getBloc(i_bloc_malus, j_bloc_malus);
    BlocNumerote* bloc_numero = (BlocNumerote*)getBloc(i_bloc_numero, j_bloc_numero);
    // Sauvegarder la valeur initiale du bloc numéroté va nous servir pour calculer la perte de points liée à la fusion avec le bloc malus
    int valeur_initiale = bloc_numero->getValeur();

    // Création d'un bloc nul pour remplacer le bloc malus
    BlocNul* bloc_nul = new BlocNul(bloc_malus->getCoord(), m_tailleBlocs);

    // La nouvelle valeur est la division de la valeur du numéroté par la valeur du malus
    int nouvelle_valeur = valeur_initiale / bloc_malus->getValeur();
    if (nouvelle_valeur < 2) {
        nouvelle_valeur = 2;  // Si la divison est strictement inférieure à 2, le bloc a la valeur 2 car c'est le minimum possible dans le jeu
    }

    // Création du nouveau bloc numéroté avec la position du bloc malus
    BlocNumerote* new_bloc = new BlocNumerote(bloc_malus->getCoord(), nouvelle_valeur, m_tailleBlocs);

    marquerNonFusionnable(i_bloc_malus, j_bloc_malus, direction);

    // Remplacer les blocs dans la grille : remplacer le bloc malus par un bloc nul, et mettre le bloc numéroté avec la nouvelle valeur à la position du malus
    setBloc(i_bloc_malus, j_bloc_malus, new_bloc);
    setBloc(i_bloc_numero, j_bloc_numero, bloc_nul);

    int perte_points = valeur_initiale - nouvelle_valeur;

    // On met cette boucle if pour que si le score est strictement inférieure à la perte de points, le score soit remis à 0
    // En effet, le score ne peut pas être négatif.
    if (m_score->getScore() < perte_points){
        m_score->reinitialiserScore();
    }
    else{
        m_score->modifierScore(-perte_points);
    }
    m_nbBlocs--;  // Une fusion libère une case dans la grille
}


void Grille::fusionnerBlocsBonusBonus(int i_bloc_bonus1, int j_bloc_bonus1, int i_bloc_bonus2, int j_bloc_bonus2,  char direction) {
    BlocBonus* bloc_bonus1 = (BlocBonus*)getBloc(i_bloc_bonus1, j_bloc_bonus1);
    BlocBonus* bloc_bonus2 = (BlocBonus*)getBloc(i_bloc_bonus2, j_bloc_bonus2);

    // Création d'un bloc nul pour remplacer les deux blocs bonus
    BlocNul* bloc_nul = new BlocNul(bloc_bonus2->getCoord(), m_tailleBlocs);

    // La nouvelle valeur est la multiplication des deux valeurs bonus
    int nouvelle_valeur = bloc_bonus1->getValeur() * bloc_bonus2->getValeur();

    // Création du nouveau bloc bonus avec la position du bloc bonus déplacé
    BlocBonus* new_bloc = new BlocBonus(bloc_bonus1->getCoord(), nouvelle_valeur, m_tailleBlocs);

    marquerNonFusionnable(i_bloc_bonus1, j_bloc_bonus1, direction);


    // Remplacer les blocs dans la grille
    setBloc(i_bloc_bonus1, j_bloc_bonus1, new_bloc);
    setBloc(i_bloc_bonus2, j_bloc_bonus2, bloc_nul);

    // Pas de mise à jour du score car il qu'il y ait au moins un bloc numéroté qui intervient dans la fusion pour avoir une modification du score
    m_nbBlocs--;  // Une fusion libère une case dans la grille
}

void Grille::fusionnerBlocsMalusMalus(int i_bloc_malus1, int j_bloc_malus1, int i_bloc_malus2, int j_bloc_malus2,  char direction) {
    BlocMalus* bloc_malus1 = (BlocMalus*)getBloc(i_bloc_malus1, j_bloc_malus1);
    BlocMalus* bloc_malus2 = (BlocMalus*)getBloc(i_bloc_malus2, j_bloc_malus2);

    // Création d'un bloc nul pour remplacer les deux blocs malus
    BlocNul* bloc_nul = new BlocNul(bloc_malus2->getCoord(), m_tailleBlocs);

    // La nouvelle valeur est la multiplication des deux valeurs malus
    int nouvelle_valeur = bloc_malus1->getValeur() * bloc_malus2->getValeur();

    // Création du nouveau bloc malus avec la position du bloc malus déplacé
    BlocMalus* new_bloc = new BlocMalus(bloc_malus1->getCoord(), nouvelle_valeur, m_tailleBlocs);

    marquerNonFusionnable(i_bloc_malus1, j_bloc_malus1, direction);

    // Remplacer les blocs dans la grille
    setBloc(i_bloc_malus1, j_bloc_malus1, new_bloc);
    setBloc(i_bloc_malus2, j_bloc_malus2, bloc_nul);

    m_nbBlocs--;  // Une fusion libère une case dans la grille
}

void Grille::fusionnerBlocsBonusMalus(int i_bloc_bonus, int j_bloc_bonus, int i_bloc_malus, int j_bloc_malus, char direction) {
    BlocBonus* bloc_bonus = (BlocBonus*)getBloc(i_bloc_bonus, j_bloc_bonus);
    BlocMalus* bloc_malus = (BlocMalus*)getBloc(i_bloc_malus, j_bloc_malus);

    // Création d'un bloc nul pour remplacer le bloc malus
    BlocNul* bloc_nul = new BlocNul(bloc_malus->getCoord(), m_tailleBlocs);

    // Détermination de la plus grande et de la plus petite valeur
    int max_valeur = std::max(bloc_bonus->getValeur(), bloc_malus->getValeur());
    int min_valeur = std::min(bloc_bonus->getValeur(), bloc_malus->getValeur());

    int nouvelle_valeur;
    if (max_valeur == min_valeur) {
        // Si les valeurs sont égales, on crée un bloc numéroté de valeur 2
        nouvelle_valeur = 2;
    } else {
        // Sinon, la nouvelle valeur est la division de la plus grande par la plus petite
        nouvelle_valeur = max_valeur / min_valeur;
    }

    // Création du nouveau bloc (bonus ou malus) avec la position du bloc bonus déplacé
    if (bloc_bonus->getValeur() > bloc_malus->getValeur()) {
        BlocBonus* new_bloc = new BlocBonus(bloc_bonus->getCoord(), nouvelle_valeur, m_tailleBlocs);
        marquerNonFusionnable(i_bloc_bonus, j_bloc_bonus, direction);
        setBloc(i_bloc_bonus, j_bloc_bonus, new_bloc);
    } else {
        BlocMalus* new_bloc = new BlocMalus(bloc_bonus->getCoord(), nouvelle_valeur, m_tailleBlocs);
        marquerNonFusionnable(i_bloc_malus, j_bloc_malus, direction);
        setBloc(i_bloc_bonus, j_bloc_bonus, new_bloc);
    }

    // Remplacement du bloc malus par un bloc nul
    setBloc(i_bloc_malus, j_bloc_malus, bloc_nul);

    // Pas de mise à jour du score car il qu'il y ait au moins un bloc numéroté qui intervient dans la fusion pour avoir une modification du score
    m_nbBlocs--;  // Une fusion libère une case dans la grille
}


bool Grille::deplacerBloc(int i, int j, char direction, bool test_finie) {
    int i_new = i, j_new = j, i_fus = i, j_fus = j;
    // bool_bord nous permettra de savoir s'il y a un bloc entre le bloc à déplacer et le bord (on regarde un des bords en fonction de la direction).
    // est_bloque nous permettra de savoir si le bloc à déplacer est côte à côte (suivant la direction choisie) avec un autre bloc ou s'il est au bord de la grille.
    bool bool_bord, est_bloque;
    Bloc* bloc_depl = getBloc(i, j); /* bloc_depl est le bloc à déplacer */

    // Détermination des nouvelles positions suivant la direction
    switch (direction) {
    case 'd': // Droite
        while (j_new + 1 < m_nbLignesCol && getBloc(i, j_new + 1)->getType() == 1) j_new++;
        j_fus = j_new + 1; // Position pour vérifier la fusion
        bool_bord = j_fus >= m_nbLignesCol; // Vérifie si on atteint le bord
        break;
    case 'g': // Gauche
        while (j_new - 1 >= 0 && getBloc(i, j_new - 1)->getType() == 1) j_new--;
        j_fus = j_new - 1; // Position pour vérifier la fusion
        bool_bord = j_fus < 0; // Vérifie si on atteint le bord
        break;
    case 'h': // Haut
        while (i_new - 1 >= 0 && getBloc(i_new - 1, j)->getType() == 1) i_new--;
        i_fus = i_new - 1; // Position pour vérifier la fusion
        bool_bord = i_fus < 0; // Vérifie si on atteint le bord
        break;
    case 'b': // Bas
        while (i_new + 1 < m_nbLignesCol && getBloc(i_new + 1, j)->getType() == 1) i_new++;
        i_fus = i_new + 1; // Position pour vérifier la fusion
        bool_bord = i_fus >= m_nbLignesCol; // Vérifie si on atteint le bord
        break;
    }

    est_bloque = (i == i_new && j == j_new); // Si le bloc n'a pas bougé, il est bloqué

    // Cas où il n'y a aucun bloc entre le bloc à déplacer et le bord
    if (bool_bord) {
        if (!test_finie) transfererBloc(i, j, i_new, j_new); // Déplacement simple si on ne teste pas la fin
        return true;
    }
    // On récupère le pointeur vers le bloc qui bloque le déplacement
    Bloc* bloc_fus = getBloc(i_fus, j_fus);

    if (!test_finie) { // Vérification des fusions uniquement si aucune fusion n'a encore été faite
        // Si deux blocs numérotés de même valeur, les fusionner
        if (bloc_depl->getType() == 2 && bloc_fus->getType() == 2) {
            BlocNumerote* bloc_num_depl = (BlocNumerote*)bloc_depl;
            BlocNumerote* bloc_num_fus = (BlocNumerote*)bloc_fus;
            if (bloc_num_depl->getValeur() == bloc_num_fus->getValeur()) {
                fusionnerBlocsNumeroteNumerote(i, j, i_fus, j_fus, direction); // Fusion avec direction
                transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
                return true; // Fusion effectuée
            }
        }
        // Si deux blocs bonus, les fusionner en restant un bloc bonus
        else if (bloc_depl->getType() == 3 && bloc_fus->getType() == 3) {
            // Fusionner les deux blocs bonus (création d'un nouveau bloc bonus à la position de fusion)
            fusionnerBlocsBonusBonus(i, j, i_fus, j_fus, direction); // Fusion avec direction
            // Transférer le bloc fusionné à la nouvelle position
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }

        // Si deux blocs malus, les fusionner en restant un malus
        else if (bloc_depl->getType() == 4 && bloc_fus->getType() == 4) {
            fusionnerBlocsMalusMalus(i, j, i_fus, j_fus, direction); // Fusion avec direction
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }
        // Si un bloc bonus et un bloc malus, les fusionner en fonction de la valeur la plus grande
        else if (bloc_depl->getType() == 3 && bloc_fus->getType() == 4) {
            fusionnerBlocsBonusMalus(i, j, i_fus, j_fus, direction); // Fusion Bonus -> Malus avec direction
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }
        // Si un bloc malus et un bloc bonus, les fusionner en fonction de la valeur la plus grande
        else if (bloc_depl->getType() == 4 && bloc_fus->getType() == 3) {
            fusionnerBlocsBonusMalus(i, j, i_fus, j_fus, direction); // Fusion Malus -> Bonus avec direction
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }
        // Si un bloc numéroté et un bloc bonus, les fusionner en un bloc numéroté
        else if (bloc_depl->getType() == 2 && bloc_fus->getType() == 3) {
            fusionnerBlocsNumeroteBonus(i, j, i_fus, j_fus, direction); // Fusion avec direction
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }
        // Si un bloc bonus et un bloc numéroté, les fusionner en un bloc numéroté
        else if (bloc_depl->getType() == 3 && bloc_fus->getType() == 2) {
            fusionnerBlocsBonusNumerote(i, j, i_fus, j_fus, direction); // Fusion avec direction
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }
        // Si un bloc numéroté et un bloc malus, les fusionner en un bloc numéroté
        else if (bloc_depl->getType() == 2 && bloc_fus->getType() == 4) {
            fusionnerBlocsNumeroteMalus(i, j, i_fus, j_fus, direction); // Fusion avec direction
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }
        // Si un bloc malus et un bloc numéroté, les fusionner en un bloc numéroté
        else if (bloc_depl->getType() == 4 && bloc_fus->getType() == 2) {
            fusionnerBlocsMalusNumerote(i, j, i_fus, j_fus, direction); // Fusion avec direction
            transfererBloc(i, j, i_fus, j_fus); // Déplacement du bloc fusionné
            return true; // Fusion effectuée
        }
    }

    // Si pas de fusion possible, déplacer le bloc simplement
    if (!est_bloque) {
        if (!test_finie) transfererBloc(i, j, i_new, j_new); // Déplacement simple
        return true;
    }
    return false;
}




bool Grille::deplacerBlocs(char direction, bool test_finie) {
    int type_bloc;
    int compt_depl = 0;
    int i_min = 0, i_max = m_nbLignesCol, i_increm = 1, j_min = 0, j_max = m_nbLignesCol, j_increm = 1;

    // Modification des variables en fonction de la direction
    switch (direction) {
    case 'd':
        j_min = m_nbLignesCol - 2;
        j_max = -1;
        j_increm = -1;
        break;
    case 'g':
        j_min = 1;
        break;
    case 'h':
        i_min = 1;
        break;
    case 'b':
        i_min = m_nbLignesCol - 2;
        i_max = -1;
        i_increm = -1;
        break;
    }

    // Déplacement et fusion des blocs
    for (int i = i_min; i != i_max; i += i_increm) {
        for (int j = j_min; j != j_max; j += j_increm) {
            Bloc* bloc_courant = getBloc(i, j);
            type_bloc = bloc_courant->getType();

            if (type_bloc == 2 || type_bloc == 3 || type_bloc == 4) {
                if (bloc_courant->getPeutFusionner()) {
                    bool deplacementEffectue = deplacerBloc(i, j, direction, test_finie);
                    if (deplacementEffectue) {
                        compt_depl++;

                        // Désactiver la fusion pour le bloc résultant
                        Bloc* nouveauBloc = getBloc(i, j);
                        if (nouveauBloc != nullptr) {
                            nouveauBloc->setPeutFusionner(false);
                        }
                    }
                }
            }
        }
    }

    // Ajout : Faire glisser tous les blocs jusqu'à trouver un bloc non nul
    if (!test_finie) {
        for (int i = 0; i < m_nbLignesCol; ++i) {
            for (int j = 0; j < m_nbLignesCol; ++j) {
                Bloc* bloc = getBloc(i, j);
                if (bloc != nullptr && bloc->getType() != 1) { // Ignorer les cases vides
                    int i_new = i, j_new = j;

                    // Déterminer la nouvelle position en fonction de la direction
                    switch (direction) {
                    case 'd': // Droite
                        while (j_new + 1 < m_nbLignesCol && getBloc(i, j_new + 1)->getType() == 1) j_new++;
                        break;
                    case 'g': // Gauche
                        while (j_new - 1 >= 0 && getBloc(i, j_new - 1)->getType() == 1) j_new--;
                        break;
                    case 'h': // Haut
                        while (i_new - 1 >= 0 && getBloc(i_new - 1, j)->getType() == 1) i_new--;
                        break;
                    case 'b': // Bas
                        while (i_new + 1 < m_nbLignesCol && getBloc(i_new + 1, j)->getType() == 1) i_new++;
                        break;
                    }

                    // Si la nouvelle position est différente, déplacer le bloc
                    if (i_new != i || j_new != j) {
                        transfererBloc(i, j, i_new, j_new);
                        compt_depl++;
                    }
                }
            }
        }
    }

    // Générer un nouveau bloc si des déplacements ont eu lieu
    if (compt_depl > 0 && !test_finie) {
        int n_alea = rand() % 30;
        if (n_alea == 0) { // 1/30 chance
            nouveauBlocBonus();
        } else if (n_alea == 1) { // 1/30 chance
            nouveauBlocMalus();
        } else { // 28/30 chance
            nouveauBlocNum();
        }
    }


    // Réactiver la fusion pour tous les blocs à la fin du mouvement
    if (!test_finie) {
        for (int i = 0; i < m_nbLignesCol; ++i) {
            for (int j = 0; j < m_nbLignesCol; ++j) {
                Bloc* bloc = getBloc(i, j);
                if (bloc != nullptr) {
                    bloc->setPeutFusionner(true);
                }
            }
        }
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

void Grille::marquerNonFusionnable(int i, int j, char direction) {
    // Si direction est 'd' (droite) ou 'g' (gauche), on marque la ligne
    if (direction == 'd' || direction == 'g') {
        for (int col = 0; col < m_nbLignesCol; ++col) {
            Bloc* bloc = getBloc(i, col);
            bloc->setPeutFusionner(false); // Marquer chaque bloc de la ligne comme non fusionnable
        }
    }
    // Si direction est 'h' (haut) ou 'b' (bas), on marque la colonne
    else if (direction == 'h' || direction == 'b') {
        for (int row = 0; row < m_nbLignesCol; ++row) {
            Bloc* bloc = getBloc(row, j);
            bloc->setPeutFusionner(false); // Marquer chaque bloc de la colonne comme non fusionnable
        }
    }
}


void Grille::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();
    for (int i = 0; i < m_nbLignesCol + 1; i++) {
        // Lorsqu'on trace un rectangle avec fillRect, alors les coordonnées (x, y) qu'on passe en paramètre correspondent au coin en haut à gauche du
        // rectangle, le coin en haut à droite correspond aux coordonneés (x + "largeur rectangle") et le coin en bas à gauche (x, y + "hauteur
        // rectangle")

        // Traçage de la colonne
        p->fillRect(x + i*(m_tailleBlocs + m_epContours), y, m_epContours, m_taille, QColor("#898080"));

        // Traçage de la ligne
        p->fillRect(x, y + i*(m_tailleBlocs + m_epContours), m_taille, m_epContours, QColor("#898080"));
    }
}

void Grille::afficherPerdu(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();

    QRect grille(x, y, m_taille, m_taille);

    QColor couleur = Qt::gray;
    couleur.setAlphaF(0.7);

    p->fillRect(grille, couleur);

    p->setPen(QPen(QColor("#000000")));
    p->setFont(QFont("Arial", m_taille/7, QFont::Bold));

    p->drawText(grille, Qt::AlignCenter, "Perdu!");
}





