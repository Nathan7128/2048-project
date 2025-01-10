#ifndef _BLOC_H_
#define _BLOC_H_



#include <QPainter>
#include <iostream>
#include <string>

using namespace std;



// Classe abstraite de base permettant de modéliser les blocs de la grille
class Bloc
{
    // Attributs protégés
protected :
    QColor m_couleur; /* Couleur du bloc (dépend de sa valeur) */
    int m_type; /* Utilisé pour la hiérarchie de classe : permet d'identifier à partir de quelle classe dérivée l'objet à été instancié.
                   On attribut le type 0 aux objets instanciés à partir de cette classe */
    static int s_epCrayon; /* Épaisseur en pixel du crayon utilisé pour tracer les blocs */

    // Méthodes publiques
public :
    Bloc(); /* Constructeur par défaut */
    QColor get_couleur(); /* Renvoie la couleur du bloc */
    virtual void dessiner(QPainter *p, int x, int y) = 0; /* Dessine le bloc dans la grille.
                            Méthode abstraite car les différentes classes dérivées n'auront pas la même implémentation de cette méthode.
                            Les paramètres x (abscicce) et y (ordonnée) correspondent au coin en haut à gauche du bloc */
    static int s_tailleBloc; /* Taille des blocs en pixel (égale à la hauteur et la largeur) */

};



#endif
