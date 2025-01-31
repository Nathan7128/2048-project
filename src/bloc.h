#ifndef _BLOC_H_
#define _BLOC_H_



#include <QPainter>
#include "coordonnees.h"
#include "exceptions.h"



// Classe abstraite de base permettant de modéliser les blocs de la grille
class Bloc
{
    // Attributs protégés
protected :
    QColor m_couleur; /* Couleur du bloc (dépend de sa valeur) */
    int m_type; /* Utilisé pour la hiérarchie de classe : permet d'identifier à partir de quelle classe dérivée l'objet à été instancié.
                   On attribut le type 0 aux objets instanciés à partir de cette classe */
    Coordonnees m_coord; /* Coordonnées x (abscisse) et y (ordonnée) du bloc exprimées en pixel */
    int m_tailleBloc; /* Taille du bloc en pixel (égale à la hauteur et la largeur du bloc) */

    // Méthodes publiques
public :
    Bloc(Coordonnees coord, int tailleBloc = 30); /* Constructeur par défaut */
    virtual ~Bloc() = default; /* Destructeur */

    // Accesseurs
    int getType();
    Coordonnees getCoord();

    // Mutateurs
    void setCoord(Coordonnees coord);

    virtual void dessiner(QPainter *p) = 0; /* Dessine le bloc dans la grille.
                            Méthode abstraite car les différentes classes dérivées n'auront pas la même implémentation de cette méthode.
                            Les paramètres x (abscicce) et y (ordonnée) correspondent au coin en haut à gauche du bloc */

};



#endif
