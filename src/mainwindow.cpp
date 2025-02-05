#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_largeur = 1000;
    m_hauteur = 700;

    int min_hauteur_largeur = min(m_hauteur, m_largeur);

    m_estFinie = 0;

    this->resize(m_largeur, m_hauteur);

    // Instanciation de la grille
    int taille_grille = min_hauteur_largeur*0.85; /* La taille de la grille correspond à la distance entre l'extérieur gauche du bord gauche et
            l'extérieur droit du bord droit, et c'est distance est donc égale à la distance entre l'extérieur haut du bord haut et l'extérieur bas du
            bord bas.
            Elle est proportionelle au minimum entre la hauteur et la largeur de la fenêtre (pour ne pas qu'elle dépasse de la fenêtre) */
    int x_grille = m_largeur/20, y_grille = (m_hauteur - taille_grille)/2;
    Coordonnees coord_grille(x_grille, y_grille);

    m_grille = new Grille(coord_grille, taille_grille, 4);

    // On récupère ensuite la taille de la grille qui a été ajustée dans le constructeur en fonction de la taille des blocs et de l'épaisseur des
    // contours calculés
    taille_grille = m_grille->getTaille();

    // Instanciation du score
    int espace_droite_grille = m_largeur - taille_grille - x_grille; /* Espace restant, horizontalement, à droite de la grille */
    int largeur_score = espace_droite_grille/2, hauteur_score = m_hauteur/6;
    int x_score = m_largeur - espace_droite_grille/2 - largeur_score/2, y_score = (m_hauteur - hauteur_score)/2;
    Coordonnees coord_score(x_score, y_score);

    m_score = new Score(coord_score, largeur_score, hauteur_score);

    // Initialisation de la grille et attribution du score
    m_grille->initialiserGrille();
    m_grille->setScore(m_score);
}

MainWindow::MainWindow(const MainWindow& m) {
    ui = m.ui;
    *m_grille = *m.m_grille;
    *m_score = *m.m_score;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_grille;
    delete m_score;
}

void MainWindow::paintEvent(QPaintEvent * e) {
    QWidget::paintEvent(e);
    QPainter painter(this);

    // Mettre le fond en blanc
    painter.fillRect(this->rect(), Qt::white);

    int nb_lignes_col = m_grille->getNbLignesCol(); /* Taille de la grille en bloc */

    m_grille->dessiner(&painter); /* Affichage de la grille sans les blocs */

    // Affichage des blocs
    for (int i = 0; i < nb_lignes_col; i++) {
        for (int j = 0; j < nb_lignes_col; j++) {
            m_grille->getBloc(i, j)->dessiner(&painter);
        }
    }

    // Affichage du score
    m_score->dessiner(&painter);

    if (m_estFinie) {
        m_grille->afficherPerdu(&painter); /* Affichage du message de défaite si la partie est finie */
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event) {

    if (!m_estFinie) {
        char direction;

        switch (event->key()) {
        case Qt::Key_Right :
            direction = 'd';
            break;
        case Qt::Key_Left :
            direction = 'g';
            break;
        case Qt::Key_Up :
            direction = 'h';
            break;
        case Qt::Key_Down :
            direction = 'b';
            break;
        }

        m_grille->deplacerBlocs(direction);

        m_estFinie = m_grille->estFinie(); /* On regarde si la partie est finie après chaque déplacement */

        this->repaint();

        // utiliser KeyRelease pour déplacer les blocs seulement si on a relaché la touche
    }
}

MainWindow& MainWindow::operator=(const MainWindow& m) {
    if (this != &m) {
        delete m_grille;
        delete m_score;
        *m_grille = *m.m_grille;
        *m_score = *m.m_score;
    }
    return *this;
}




