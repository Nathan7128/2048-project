#ifndef _GRILLE_H_
#define _GRILLE_H_



#include "blocnumerote.h"
#include "blocnul.h"
#include <string.h>

using namespace std;



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
    Bloc * getBloc(int i, int j); /* Renvoie le pointeur de bloc contenu dans la case située à la ligne i et la colonne j */
    void setBloc(int i, int j, Bloc * bloc);
    void nouveauBlocNum(); /* Place un nouveau bloc numéroté dans la grille avec une valeur aléatoirement choisie parmi 2 et 4 (avec des probabilités
            respectivement égales à 3/4 et 1/4. Lorsqu'on créé un nouveau bloc numéroté, il est placé aléatoirement.
            On va donc déterminer dans cette méthode la case ou va se trouver ce nouveau bloc */
    void initialiserGrille(); /* Initialise la grille en la remplissant de blocs nuls et de 2 blocs numérotés placés aléatoirement dans la grille */
    void deplacerBloc(int i_old, int j_old, int i_new, int j_new); /* Déplace un bloc situé à la ligne i et la colonne j de la grille jusqu'à la
                ligne i_new et la colonne j_new de la grille */
    void fusionnerBlocs(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus); /* Fusionne 2 blocs numérotés de la grille.
                        Une fusion est le fait de déplacer un bloc numéroté vers un autre bloc numéroté qui possède la même valeur, et ainsi
                        d'obtenir un nouveau bloc numéroté d'une valeur égale à deux fois la valeur des blocs à fusionner.
                        Les entiers "i_bloc_depl" et "j_bloc_depl" correspondent à la ligne et la colonne de la case qui contient le pointeur vers le
                        bloc à déplacer. Après avoir déplacer et fusionner ce bloc, on va placer un pointeur vers un bloc nul dans la case qui le
                        contenait.
                        Les entiers "i_bloc_fus" et "j_bloc_fus" correspondent à la ligne et la colonne de la case qui contient le pointeur vers le
                        bloc qui va être fusionner avec le bloc à déplacer. Ce bloc sera donc remplacé par le bloc résultant de la fusion réalisée. */
    void deplacerDroite(int i, int j); /* Permet de déplacer un bloc situé à la ligne i et la colonne j de la grille vers la droite */
    void deplacerGauche(int i, int j); /* Permet de déplacer un bloc situé à la ligne i et la colonne j de la grille vers la gauche */
    void deplacerHaut(int i, int j); /* Permet de déplacer un bloc situé à la ligne i et la colonne j de la grille vers le haut */
    void deplacerBas(int i, int j); /* Permet de déplacer un bloc situé à la ligne i et la colonne j de la grille vers le bas */
    void deplacerBlocs(char direction); /* Permet de déplacer (ou non s'ils sont bloqués) l'ensemble des blocs numérotés dans une direction saisie
            grâce aux 4 touches fléchées du clavier. Lorsqu'on effectue un déplacement, on n'essaye pas de déplacer les blocs qui sont sur le bord de
            la grille car ils sont bloqués (par le bord de la grille) et ne pourrons pas être déplacés dans tous les cas. Par exemple, si on déplace
            les blocs vers la droite, on n'essaiera pas de déplacer les blocs de la colonne la plus à droite */
    int estFinie(); /* Retourne 0 si le partie est terminée et 1 si il y a encore des déplacements possible. On vérifie si la partie est finie à chaque
            tour ou la grille est remplie de blocs numérotés, c'est à dire à chaque tour ou m_nbBlocs = m_tailleGrille*m_tailleGrille */

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
