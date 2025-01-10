#ifndef _GRILLE_H_
#define _GRILLE_H_



#include "blocnumerote.h"
#include "blocnul.h"



// Classe permettant de modéliser la grille du 2048.
// Cette grille possède le même nombre de lignes et de colonnes, et chaque case de cette dernière est composée d'un bloc
class Grille {
    // Attributs protégés
protected :
    int m_taille; /* Nombre de lignes et de colonnes de la grille : si m_taille = 4, alors la grille est de taille 4x4 */
    Bloc*** m_matBloc; /* Matrice de pointeurs vers des objets de type "Bloc" : cette matrice correspond à la grille */
    int m_nbBloc; /* Nombre de blocs numérotés dans la grille à un instant t (nombre de cases non vides) */

    // Déclaration des méthodes
public :
    Grille(int taille = 4); /* Constructeur par défaut qui prend en paramètre la taille de la grille : la taille par défaut est 4
                               La grille est initialement remplie de blocs nuls */
    int getTaille(); /* Renvoie la taille de la grille */
    int getNbBloc(); /* Renvoie le nombre de blocs numérotés actuellement présents dans la grille */
    void modifierCase(Bloc bloc, int i, int j); /* Permet de modifier le contenu de la case située à la ligne i
                                                   et la colonne j de la grille */
    void initialiser(); /* Permet d'initialiser la grille avec 2 blocs aléatoirement placés.
                           Ces blocs prennent la valeur 2 ou 4 */
    void afficher(); /* Permet d'afficher la grille */
    Bloc* obtenirCase(); /* Permet d'obtenir le pointeur de bloc situé à la ligne i et la colonne j */
    void deplacerBlocs(string direction, int i, int j); /* Permet de déplacer les blocs de la grille en fonction d'une direction */
};



#endif // !_GRILLE_H_
