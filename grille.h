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
    BlocNumerote* nouveauBlocNum(int i, int j, int valeur); /* Instancie un nouveau bloc numéroté avec une valeur passée en paramètre
                        Le bloc sera situé à la ligne i et la colonne j de la matrice (grille).
                        En fonction de i et j, on pourra déterminer en pixel les coordonnées du bloc dans la grille */
    BlocNumerote* nouveauBlocNum(int i, int j); /* Surchage de la méthode permettant d'instancier un nouveau bloc avec
                                                   une valeur choisie aléatoirement parmi 2 et 4 */
    BlocNul* nouveauBlocNul(int i, int j); /* Instancie un nouveau bloc nul, de la même manière que la méthode nouveauBlocNum */
    void placerBlocNum(int i, int j); /* Place un nouveau bloc numéroté avec une position aléatoire dans la grille */
    void initialiserGrille(); /* Initialise la grille en la remplissant de blocs nuls et de 2 blocs numérotés */

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
