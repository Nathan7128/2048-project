#include "blocnumerote.h"



BlocNumerote::BlocNumerote(int valeur) {
    m_type = 2;
    m_valeur = valeur;

    // Attribution de la couleur du bloc à l'aide d'un switch en fonction de la valeur
    switch (valeur) {
    case 2 :
        m_couleur = "#eeed4a";
        break;
    case 4 :
        m_couleur = "#ede0c8";
        break;
    case 8 :
        m_couleur = "#f2b179";
        break;
    case 16 :
        m_couleur = "#f59563";
        break;
    case 32 :
        m_couleur = "#f67c5f";
        break;
    case 64 :
        m_couleur = "#f65e3b";
        break;
    case 128 :
        m_couleur = "#edcf72";
        break;
    case 256 :
        m_couleur = "#edcc61";
        break;
    case 512 :
        m_couleur = "#edc850";
        break;
    case 1024 :
        m_couleur = "#edc53f";
        break;
    case 2048 :
        m_couleur = "#edc22e";
        break;
    default :
        m_couleur = "#000000";
    }
}

void BlocNumerote::dessiner(QPainter *p, int x, int y) {
    p->setPen(QPen(QColor("#7c7c7c"), s_epCrayon));
    p->drawRect(x, y, s_tailleBloc, s_tailleBloc);
    p->fillRect(x + s_epCrayon, y + s_epCrayon, s_tailleBloc - s_epCrayon, s_tailleBloc - s_epCrayon, QBrush(m_couleur));
    p->setPen(QPen(QColor("#000000"), s_epCrayon));
    p->setFont(QFont("Arial", 16));
    p->drawText(10, 30, QString::number(m_valeur));
}

int BlocNumerote::getValeur() {
    return m_valeur;
}
