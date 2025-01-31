#include "blocnumerote.h"



BlocNumerote::BlocNumerote(Coordonnees coord, int valeur, int taille_bloc):Bloc(coord, taille_bloc) {
    m_type = 2;
    m_valeur = valeur;

    // Définition de la police d'écriture
    int log_valeur = log10(valeur), taille_police;
    switch (log_valeur) {
    case 0:
        taille_police = taille_bloc*0.45;
        break;
    case 1:
        taille_police = taille_bloc*0.4;
        break;
    case 2:
        taille_police = taille_bloc*0.35;
        break;
    case 3:
        taille_police = taille_bloc*0.3;
        break;
    }

    m_font = QFont("Arial", taille_police, QFont::Bold);

    // Attribution de la couleur du bloc à l'aide d'un switch en fonction de la valeur
    switch (valeur) {
    case 2 :
        m_couleur = QColor("#eee4da");
        break;
    case 4 :
        m_couleur = QColor("#ede0c8");
        break;
    case 8 :
        m_couleur = QColor("#f2b179");
        break;
    case 16 :
        m_couleur = QColor("#f59563");
        break;
    case 32 :
        m_couleur = QColor("#f67c5f");
        break;
    case 64 :
        m_couleur = QColor("#f65e3b");
        break;
    case 128 :
        m_couleur = QColor("#edcf72");
        break;
    case 256 :
        m_couleur = QColor("#edcc61");
        break;
    case 512 :
        m_couleur = QColor("#edc850");
        break;
    case 1024 :
        m_couleur = QColor("#edc53f");
        break;
    case 2048 :
        m_couleur = QColor("#edc22e");
        break;
    case 4096 :
        m_couleur = QColor("#8f50e7");
        break;
    default :
        m_couleur = QColor("#000000");
    }
}

int BlocNumerote::getValeur() {
    return m_valeur;
}

void BlocNumerote::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();
    QRect bloc(x, y, m_tailleBloc, m_tailleBloc);

    // Affichage du bloc
    p->fillRect(bloc, m_couleur);

    // Affichage de la valeur du bloc
    p->setPen(QPen(QColor("#000000")));
    p->setFont(m_font);
    p->drawText(bloc, Qt::AlignCenter, QString::number(m_valeur));
}
