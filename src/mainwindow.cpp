#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_largeur = 1200;
    m_hauteur = 600;
    m_estFinie = 0;

    this->resize(m_largeur, m_hauteur);

    // Instanciation de la grille
    int taille_grille = m_hauteur * 0.9;
    int x_grille = m_largeur / 15, y_grille = (m_hauteur - taille_grille) / 2;
    Coordonnees coord_grille(x_grille, y_grille);

    m_grille = new Grille(coord_grille, taille_grille, 4);

    // Instanciation du score
    int espace_droite_grille = m_largeur - taille_grille - x_grille; /* Espace restant, horizontalement, à droite de la grille */
    int largeur_score = (m_largeur - espace_droite_grille) / 3, hauteur_score = m_hauteur / 6;
    int x_score = m_largeur - espace_droite_grille / 2 - largeur_score / 2, y_score = (m_hauteur - hauteur_score) / 2;
    Coordonnees coord_score(x_score, y_score);

    m_score = new Score(coord_score, largeur_score, hauteur_score);

    // Initialisation de la grille et attribution du score
    m_grille->initialiserGrille();
    m_grille->setScore(m_score);

    // Création du bouton Relancer
    m_boutonRelancer = new QPushButton("Relancer", this);

    // Définir manuellement les coordonnées et taille du bouton Relancer
    int largeur_bouton = largeur_score; // Même largeur que le bouton score
    int hauteur_bouton = hauteur_score; // Même hauteur que le bouton score

    // Placer le bouton juste au-dessus du score
    int x_boutonRelancer = x_score; // Même position horizontale que le score
    int y_boutonRelancer = y_score - hauteur_bouton - 50; // 50 pixels au-dessus du score

    // Police 14 pour le bouton Relancer
    m_boutonRelancer->setFont(QFont("Arial", 14, QFont::Bold));


    m_boutonRelancer->setGeometry(x_boutonRelancer, y_boutonRelancer, largeur_bouton, hauteur_bouton); // Définir la géométrie du bouton
    m_boutonRelancer->setStyleSheet("background-color: #898080; color: white; font-weight: bold;"); // Style du bouton


    // Empêche le bouton de capturer le focus
    // Ca permet de pouvoir utiliser les touches du clavier ou relancer la partie à n'importe quel moment
    m_boutonRelancer->setFocusPolicy(Qt::NoFocus);


    // Connecter le bouton Relancer au slot de réinitialisation
    connect(m_boutonRelancer, &QPushButton::clicked, this, &MainWindow::relancerPartie);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_grille;
    delete m_score;
    delete m_boutonRelancer;
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
        default :
            return; // Ne rien faire si une mauvaise touche est utilisée
        }

        m_grille->deplacerBlocs(direction);

        m_estFinie = m_grille->estFinie(); /* On regarde si la partie est finie après chaque déplacement */

        this->repaint();
    }
}


void MainWindow::relancerPartie() {
    // Libérer la mémoire des anciens objets (évite les fuites de mémoire)
    delete m_grille;
    delete m_score;

    // Réinitialiser la grille et le score
    int taille_grille = m_hauteur * 0.9;
    int x_grille = m_largeur / 15, y_grille = (m_hauteur - taille_grille) / 2;
    Coordonnees coord_grille(x_grille, y_grille);

    m_grille = new Grille(coord_grille, taille_grille, 4);

    // Créer le score avec des nouvelles coordonnées
    int espace_droite_grille = m_largeur - taille_grille - x_grille;
    int largeur_score = (m_largeur - espace_droite_grille) / 3, hauteur_score = m_hauteur / 6;
    int x_score = m_largeur - espace_droite_grille / 2 - largeur_score / 2, y_score = (m_hauteur - hauteur_score) / 2;
    Coordonnees coord_score(x_score, y_score);

    m_score = new Score(coord_score, largeur_score, hauteur_score);

    // Lier le score à la grille
    m_grille->setScore(m_score);

    m_estFinie = 0;  // Partie en cours

    // Réinitialiser la grille
    m_grille->initialiserGrille();

    // Redessiner l'interface
    this->repaint();
}






