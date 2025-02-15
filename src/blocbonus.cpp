#include "blocbonus.h"


BlocBonus::BlocBonus(Coordonnees coord, int valeur, int taille_bloc):Bloc(coord, taille_bloc) {
    m_type = 3;  // Type pour les blocs bonus
    m_valeur = valeur;

    // Définition de la police d'écriture en fonction de la valeur
    int log_valeur = log10(valeur), taille_police;
    switch (log_valeur) {
    case 0:
        taille_police = taille_bloc * 0.45;
        break;
    case 1:
        taille_police = taille_bloc * 0.4;
        break;
    case 2:
        taille_police = taille_bloc * 0.35;
        break;
    case 3:
        taille_police = taille_bloc * 0.3;
        break;
    case 4:
        taille_police = taille_bloc * 0.25;
        break;
    }

    m_font = QFont("Arial", taille_police, QFont::Bold);

    // Attribution de la couleur du bloc bonus en fonction de la valeur
    switch (valeur) {
    case 2:
        m_couleur = QColor("#c0f0c0");  // Vert clair
        break;
    case 4:
        m_couleur = QColor("#99e699");  // Vert pastel
        break;
    case 8:
        m_couleur = QColor("#66cc66");  // Vert plus foncé
        break;
    case 16:
        m_couleur = QColor("#33cc33");  // Vert frais
        break;
    case 32:
        m_couleur = QColor("#28a828");  // Vert profond
        break;
    case 64:
        m_couleur = QColor("#1f9e1f");  // Vert intense
        break;
    case 128:
        m_couleur = QColor("#1a8d1a");  // Vert vibrant
        break;
    case 256:
        m_couleur = QColor("#178b17");  // Vert éclatant
        break;
    case 512:
        m_couleur = QColor("#147f14");  // Vert émeraude
        break;
    case 1024:
        m_couleur = QColor("#107a10");  // Vert forêt
        break;
    case 2048:
        m_couleur = QColor("#0f771f");  // Vert sapin
        break;
    case 4096:
        m_couleur = QColor("#0f6b1b");  // Vert mousse
        break;
    case 8192:
        m_couleur = QColor("#0d6017");  // Vert profond (le plus élevé)
        break;
    default:
        m_couleur = QColor("#000000");  // Noir (si valeur erronée)
    }
}

int BlocBonus::getValeur() {
    return m_valeur;
}

void BlocBonus::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();
    QRect bloc(x, y, m_tailleBloc, m_tailleBloc);
    p->fillRect(bloc, m_couleur);
    p->setPen(QPen(QColor("#000000")));
    p->setFont(m_font);
    p->drawText(bloc, Qt::AlignCenter, "×" + QString::number(m_valeur));
}

