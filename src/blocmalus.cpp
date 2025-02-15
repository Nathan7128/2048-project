#include "blocmalus.h"

BlocMalus::BlocMalus(Coordonnees coord, int valeur, int taille_bloc):Bloc(coord, taille_bloc) {
    m_type = 4;  // Type pour les blocs malus
    m_valeur = valeur;

    // Définition de la police d'écriture
    // La police est toujours la même car contient toujours deux caractères ("*" + "2", "4", ou "8")
    int taille_police;
    taille_police = taille_bloc * 0.40;

    m_font = QFont("Arial", taille_police, QFont::Bold);

    // Attribution de la couleur du bloc malus en fonction de la valeur
    switch (valeur) {
    case 2:
        m_couleur = QColor("#FF6666");  // Rouge clair
        break;
    case 4:
        m_couleur = QColor("#FF4D4D");  // Rouge plus saturé
        break;
    case 8:
        m_couleur = QColor("#FF3333");  // Rouge intense
        break;
    case 16:
        m_couleur = QColor("#FF1A1A");  // Rouge profond
        break;
    case 32:
        m_couleur = QColor("#FF0000");  // Rouge vif
        break;
    case 64:
        m_couleur = QColor("#E60000");  // Rouge foncé
        break;
    case 128:
        m_couleur = QColor("#B20000");  // Rouge sombre
        break;
    case 256:
        m_couleur = QColor("#800000");  // Rouge bordeaux
        break;
    case 512:
        m_couleur = QColor("#660000");  // Rouge cramoisi
        break;
    case 1024:
        m_couleur = QColor("#4D0000");  // Rouge sang
        break;
    case 2048:
        m_couleur = QColor("#3D0000");  // Rouge très foncé
        break;
    case 4096:
        m_couleur = QColor("#2E0000");  // Rouge sombre
        break;
    case 8192:
        m_couleur = QColor("#1F0000");  // Rouge intense (le plus élevé)
        break;
    default:
        m_couleur = QColor("#000000");  // Noir (si valeur erronée)
    }
}


int BlocMalus::getValeur() {
    return m_valeur;
}

void BlocMalus::dessiner(QPainter *p) {
    int x = m_coord.getX(), y = m_coord.getY();
    QRect bloc(x, y, m_tailleBloc, m_tailleBloc);
    p->fillRect(bloc, m_couleur);
    p->setPen(QPen(QColor("#000000")));
    p->setFont(m_font);
    p->drawText(bloc, Qt::AlignCenter, "/" + QString::number(m_valeur));
}

