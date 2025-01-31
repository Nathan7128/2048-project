#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
// Ce fichier source regroupe l'ensemble des exceptions appliquées à ce programme.
// Ces exceptions sont implémentées sous forme de classe.



#include <string.h>
#include <iostream>

using namespace std;



// Exception si les coordonnées en pixel d'un objet sont négatives
class ExceptionCoordNeg {
public:
    string m_message;
    ExceptionCoordNeg(string m = "") {m_message = m;};
};

// Exception si la ligne/colonne indiquée pour un élément de la matrice de la grille est négative
class ExceptionLigneColNeg {
public:
    string m_message;
    ExceptionLigneColNeg(string m = "") {m_message = m;};
};

// Exception si le nombre de lignes (= nombre de colonnes) de la grille du 2048 est < 2
class ExceptionNbLignesCol {
public:
    string m_message;
    ExceptionNbLignesCol(string m = "") {m_message = m;};
};

// Exception si la taille (largeur ou hauteur) d'un objet graphique (grille, bloc, etc.) est négative
class ExceptionTailleObjet {
public:
    string m_message;
    ExceptionTailleObjet(string m = "") {m_message = m;};
};

// Exception si la valeur d'un bloc n'est pas une puissance de 2
class ExceptionValeurBloc {
public:
    string m_message;
    ExceptionValeurBloc(string m = "") {m_message = m;};
};

// Exception si on essaye d'ajouter un nouveau bloc dans la grille alors qu'elle est pleine
class ExceptionGrillePleine {
public:
    string m_message;
    ExceptionGrillePleine(string m = "") {m_message = m;};
};



#endif // EXCEPTIONS_H
