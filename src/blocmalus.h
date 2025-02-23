#ifndef BLOCMALUS_H
#define BLOCMALUS_H

#include "bloc.h"

// Classe héritée de la classe de base bloc.
// Cette classe permet de modéliser les blocs numérotés auxquels on attribue une valeur et une couleur (dépendant de la valeur)
class BlocMalus : public Bloc
{
    // Attributs protégés
protected :
    int m_valeur; /* Valeur attribuée au bloc */
    QFont m_font; /* Police utilisée pour écrire la valeur du bloc à l'intérieur de la case */

    // Méthodes publiques
public :
    BlocMalus(Coordonnees coord, int valeur = 2, int taille_bloc = 30); /* Constructeur par défaut : on attribue le type 3 aux blocs malus.
                                                                                Le constructeur prend en paramètre une valeur, et on définira la couleur du bloc en fonction de cette dernière */
    ~BlocMalus() {};

    // Accesseurs
    virtual int getValeur() const;

    void dessiner(QPainter *p); /* Dessine le bloc numéroté dans la grille */
};

#endif // BLOCMALUS_H
