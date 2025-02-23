#include "record.h"
#include <cmath>

Record::Record(Coordonnees coord, int largeur, int hauteur, int valeurInitiale)
{
    m_coord = coord;
    m_largeur = largeur;
    m_hauteur = hauteur;
    m_record = valeurInitiale;
}

void Record::modifierRecord(int valeur) {
    m_record = valeur;
}

int Record::getRecord() const {
    return m_record;
}

void Record::reinitialiserRecord() {
    m_record = 0;
}

void Record::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();

    // Affichage du rectangle gris contenant le record
    QRect rect_record(x, y, m_largeur, m_hauteur);
    p->fillRect(rect_record, QColor("#898080"));

    p->setPen(QPen(QColor("#ffffff")));

    // Affichage du texte "RECORD"
    int hauteur_rect_texte = m_hauteur / 6;
    int y_rect_texte = y + m_hauteur / 6;
    QRect rect_texte(x, y_rect_texte, m_largeur, hauteur_rect_texte);

    p->setFont(QFont("Arial", hauteur_rect_texte * 0.7, QFont::Bold));
    p->drawText(rect_texte, Qt::AlignHCenter, "RECORD");

    // Affichage de la valeur du record
    int y_rect_valeur = y_rect_texte + hauteur_rect_texte;
    int hauteur_rect_valeur = m_hauteur - y_rect_valeur + y;
    QRect rect_valeur(x, y_rect_valeur, m_largeur, hauteur_rect_valeur);

    int log_valeur = (m_record > 0 ? static_cast<int>(log10(m_record)) : 0), taille_police;
    switch (log_valeur) {
    case 1:
        taille_police = hauteur_rect_valeur * 0.5;
        break;
    case 2:
        taille_police = hauteur_rect_valeur * 0.45;
        break;
    case 3:
        taille_police = hauteur_rect_valeur * 0.4;
        break;
    case 4:
        taille_police = hauteur_rect_valeur * 0.35;
        break;
    case 5:
        taille_police = hauteur_rect_valeur * 0.3;
        break;
    default:
        taille_police = hauteur_rect_valeur * 0.55;
    }

    p->setFont(QFont("Arial", taille_police, QFont::Bold));
    p->drawText(rect_valeur, Qt::AlignCenter, QString::number(m_record));
}
