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
    QFont m_font; /* Police utilisée pour écrire la valeur du bloc à l'intérieur de la case */

    // Méthodes publiques
public :
    BlocNumerote(Coordonnees coord, int valeur = 2, int taille_bloc = 30); /* Contructeur par défaut : on attribue le type 2 aux blocs numérotés.
                                                                                Le contructeur prend en paramètre une valeur, et on définira la couleur du bloc en fonction de cette dernière */
    ~BlocNumerote() {};

    // Accesseurs
    virtual int getValeur() const ;

    void dessiner(QPainter *p); /* Dessine le bloc numéroté dans la grille */
};





#endif // !_BLOCNUMEROTE_H_
