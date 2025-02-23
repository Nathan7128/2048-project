#ifndef _RECORDGENERAL_H_
#define _RECORDGENERAL_H_

#include "coordonnees.h"
#include <QPainter>
#include <QString>

class RecordGeneral {
public:
    // Le constructeur avec possibilité d'initialiser le record général (par défaut 0) et le nom (par défaut "Invité")
    RecordGeneral(Coordonnees coord, int largeur, int hauteur, int valeurInitiale = 0, const QString &nomInitial = "Invité");

    void modifierRecordGeneral(int valeur, const QString &nom);
    int getRecordGeneral() const;
    QString getNomRecord() const;
    void reinitialiserRecordGeneral();

    // Charge le record global depuis le fichier "record_global/record_general.txt"
    bool chargerRecordGeneral();
    // Sauvegarde le record global dans le fichier "record_global/record_general.txt"
    bool sauvegarderRecordGeneral();

    void dessiner(QPainter *p);

private:
    Coordonnees m_coord;
    int m_largeur;
    int m_hauteur;
    int m_recordgeneral;
    QString m_nomRecord;
};

#endif // _RECORDGENERAL_H_
