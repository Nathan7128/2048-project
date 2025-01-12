#include "blocnumerote.h"



int BlocNumerote::s_epCrayonTexte = 1;

BlocNumerote::BlocNumerote(QColor couleur, int type, int x, int y, int valeur):Bloc(couleur, type, x, y) {
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

void BlocNumerote::dessiner(QPainter *p) {
    p->fillRect(m_x, m_y, s_tailleBloc, s_tailleBloc, QBrush(m_couleur));
    p->setPen(QPen(QColor("#000000"), s_epCrayonTexte));
    p->setFont(QFont("Arial", 16));
    p->drawText(m_x + 20, m_y + 20, QString::number(m_valeur));
}

int BlocNumerote::getValeur() {
    return m_valeur;
}
