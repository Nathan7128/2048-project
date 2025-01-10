#ifndef _BLOCNUL_H_
#define _BLOCNUL_H_



#include "Bloc.h"



// Classe héritée de la classe de base bloc.
// Cette classe permet de modéliser les blocs nuls de la grille qui correspondent aux cases vides
class BlocNul : public Bloc
{
    // Méthodes publiques
public :
    BlocNul(); /* Constructeur par défaut : on attribue par défaut le type 1 aux blocs nuls et la couleur grise */
    void dessiner(QPainter *p, int x, int y); /* Dessine le bloc nul dans la grille */
};



#endif // !_BLOCNUL_H_
