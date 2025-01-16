#ifndef _GRILLE_H_
#define _GRILLE_H_



#include "blocnumerote.h"
#include "blocnul.h"



// Classe permettant de modéliser la grille du 2048.
// Cette grille possède le même nombre de lignes et de colonnes, et chaque case de cette dernière est composée d'un bloc
class Grille {
    // Attributs protégés
protected :
    Bloc*** m_matBlocs; /* Matrice de pointeurs vers des objets de type "Bloc" : cette matrice correspond à la grille */
    int m_nbBlocs; /* Nombre de blocs non nuls dans la grille à un instant t (nombre de cases non vides) */
    int m_x; /* Coordonnée (abscisse) du coin en haut à gauche de la grille */
    int m_y; /* Coordonnée (ordonnée) du coin en haut à gauche de la grille */
    int m_hauteurGrille ; /* Hauteur de la grille en pixel */
    int m_largeurGrille ; /* Largeur de la grille en pixel */
    int m_tailleGrille; /* Nombre de lignes et de colonnes de la grille : si m_taille = 4, alors la grille est de taille 4x4 */
    int m_tailleBlocs; /* Taille de tous les blocs de la grille (ils font tous la même taille)
                       La taille du bloc correspond à sa largeur et à sa hauteur */
    int m_epCountour; /* Epaisseur du crayon utilisé pour tracer les contours extérieurs et intérieurs de la grille.
                         Les countours intérieurs correspondent aux traits de séparation entre les différents blocs */

    // Déclaration des méthodes
public :
    Grille(int x = 0, int y = 0, int hauteurGrille = 120, int largeurGrille = 120, int tailleGrille = 4); /* Constructeur par défaut */
    void nouveauBlocNum(); /* Place un nouveau bloc numéroté dans la grille avec une valeur aléatoirement choisie parmi 2 et 4 (avec des probabilités
            respectivement égales à 3/4 et 1/4. Lorsqu'on créé un nouveau bloc numéroté, il est placé aléatoirement.
            On va donc déterminer dans cette méthode la case ou va se trouver ce nouveau bloc */
    void nouveauBlocNul(int i, int j); /* Place un nouveau bloc nul dans la grille. Lorsqu'on créé un nouveau bloc nul, on connait déjà sa position */
    void initialiserGrille(); /* Initialise la grille en la remplissant de blocs nuls et de 2 blocs numérotés placés aléatoirement dans la grille */
    void fusionnerBlocs(int i_bloc1, int j_bloc1, int i_bloc2, int j_bloc2); /* Fusionne 2 blocs numérotés de la grille.
                                On part du principe qu'on les fusionne dans la case du bloc 1 : on déplace le bloc 2 vers le bloc 1 */

    // int getNbBloc(); /* Renvoie le nombre de blocs non nuls actuellement présents dans la grille */
    // void modifierCase(Bloc bloc, int i, int j); /* Permet de modifier le contenu de la case située à la ligne i
    //                                                et la colonne j de la grille */
    // void initialiser(); /* Permet d'initialiser la grille avec 2 blocs aléatoirement placés.
    //                        Ces blocs prennent la valeur 2 ou 4 */
    // void afficher(); /* Permet d'afficher la grille */
    // Bloc* obtenirCase(); /* Permet d'obtenir le pointeur de bloc situé à la ligne i et la colonne j */
    // void deplacerBlocs(string direction, int i, int j); /* Permet de déplacer les blocs de la grille en fonction d'une direction */
};



#endif // !_GRILLE_H_
