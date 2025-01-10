#ifndef _BLOCNUMEROTE_H_
#define _BLOCNUMEROTE_H_



#include "bloc.h"



// Classe héritée de la classe de base bloc.
// Cette classe permet de modéliser les blocs numérotées auxquels on attribue une valeur et une couleur (dépendant de la valeur)
class BlocNumerote : public Bloc
{
    // Attributs protégés
protected :
    int m_valeur; /* Valeur attribuée au bloc */

    // Méthodes publiques
public :
    BlocNumerote(int valeur); /* Contructeur par défaut : on attribue le type 2 aux blocs numérotés. Le contructeur prend en paramètre une
                                 valeur, et on définira la couleur du bloc en fonction de cette dernière */
    void dessiner(QPainter *p, int x, int y); /* Dessine le bloc numéroté dans la grille */
    int getValeur(); /* Retourne la valeur du bloc */
};





#endif // !_BLOCNUMEROTE_H_
