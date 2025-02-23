#include "recordgeneral.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <cmath>

RecordGeneral::RecordGeneral(Coordonnees coord, int largeur, int hauteur, int valeurInitiale, const QString &nomInitial)
{
    m_coord = coord;
    m_largeur = largeur;
    m_hauteur = hauteur;
    m_recordgeneral = valeurInitiale;
    m_nomRecord = nomInitial;
}

void RecordGeneral::modifierRecordGeneral(int valeur, const QString &nom)
{
    m_recordgeneral = valeur;
    m_nomRecord = nom;
}

int RecordGeneral::getRecordGeneral() const
{
    return m_recordgeneral;
}

QString RecordGeneral::getNomRecord() const
{
    return m_nomRecord;
}

void RecordGeneral::reinitialiserRecordGeneral()
{
    m_recordgeneral = 0;
    m_nomRecord = "Invité";
}

bool RecordGeneral::chargerRecordGeneral()
{
    QDir dossier("record_general");
    if (!dossier.exists())
        dossier.mkpath("record_general");

    QString cheminFichier = dossier.filePath("record_general.txt");
    QFile fichier(cheminFichier);
    if (!fichier.exists()) {
        if (fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&fichier);
            out << "Invité\n" << "0\n";
            fichier.close();
        } else {
            return false;
        }
    }
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&fichier);
    m_nomRecord = in.readLine().trimmed();
    QString scoreStr = in.readLine().trimmed();
    m_recordgeneral = scoreStr.toInt();
    fichier.close();
    return true;
}

bool RecordGeneral::sauvegarderRecordGeneral()
{
    QDir dossier("record_general");
    if (!dossier.exists())
        dossier.mkpath("record_general");

    QString cheminFichier = dossier.filePath("record_general.txt");
    QFile fichier(cheminFichier);
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&fichier);
    out << m_nomRecord << "\n" << m_recordgeneral << "\n";
    fichier.close();
    return true;
}

void RecordGeneral::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();

    // Affichage du rectangle gris de fond
    QRect rect_record(x, y, m_largeur, m_hauteur);
    p->fillRect(rect_record, QColor("#898080"));
    p->setPen(QPen(QColor("#ffffff")));

    // Affichage du texte "RECORD GÉNÉRAL"
    int hauteur_rect_texte = m_hauteur / 6;
    int y_rect_texte = y + m_hauteur / 8;
    QRect rect_texte(x, y_rect_texte, m_largeur, hauteur_rect_texte);
    p->setFont(QFont("Arial", hauteur_rect_texte * 0.7, QFont::Bold));
    p->drawText(rect_texte, Qt::AlignHCenter, "RECORD GÉNÉRAL");

    // Affichage du nom du détenteur en dessous du libellé
    int hauteur_nom = hauteur_rect_texte;  // hauteur du nom (ajustable)
    int y_nom = y_rect_texte + hauteur_rect_texte;
    QRect rect_nom(x, y_nom, m_largeur, hauteur_nom);
    p->setFont(QFont("Arial", 0.7*hauteur_nom, QFont::Bold));  // police plus petite
    p->drawText(rect_nom, Qt::AlignHCenter, m_nomRecord);


    // Affichage de la valeur du record général en dessous du nom
    int y_rect_valeur = y_nom + hauteur_nom;
    int hauteur_rect_valeur = m_hauteur - y_rect_valeur + y;
    QRect rect_valeur(x, y_rect_valeur, m_largeur, hauteur_rect_valeur);

    // Pour gérer le log de 0
    int log_valeur = (m_recordgeneral > 0 ? int(log10(m_recordgeneral)) : 0);
    int taille_police;
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
    p->drawText(rect_valeur, Qt::AlignCenter, QString::number(m_recordgeneral));
}
