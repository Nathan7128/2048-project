#ifndef COORDONNEES_H
#define COORDONNEES_H



// Classe permettant de modéliser les coordonnées x (abscisse) et y (ordonnée) d'un objet de la fenêtre "MainWindow".
// Ces coordonnées sont exprimées en pixel
class Coordonnees {
    // Attributs protégés
protected :
    int m_x; /* Abscisse de l'objet */
    int m_y; /* Ordonnée de l'objet */

    // Méthodes publiques
public:
    Coordonnees(int x = 0, int y = 0); /* Constructeur par défaut */

    // Accesseurs
    int getX();
    int getY();

    // Mutateurs
    void setX(int x);
    void setY(int y);

};

#endif // COORDONNEES_H
