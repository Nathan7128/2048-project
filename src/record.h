#ifndef _RECORD_H_
#define _RECORD_H_

#include "coordonnees.h"
#include <QPainter>

class Record {
public:
    // Le constructeur accepte un paramètre optionnel 'valeurInitiale' (par défaut 0)
    Record(Coordonnees coord, int largeur, int hauteur, int valeurInitiale = 0);

    void modifierRecord(int valeur);
    int getRecord() const;
    void reinitialiserRecord();
    void dessiner(QPainter *p);

private:
    Coordonnees m_coord;
    int m_largeur;
    int m_hauteur;
    int m_record;
};

#endif // _RECORD_H_
