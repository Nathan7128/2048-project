#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Utilisateur de type Invité par défaut
    m_utilisateur = new Utilisateur("Invité");
    m_recordInvite = 0;
    m_nbLignesCol = 4;  // Dimension par défaut de la grille

    m_largeur = 1200;
    m_hauteur = 600;
    m_estFinie = 0;
    this->resize(m_largeur, m_hauteur);

    // Instanciation de la grille
    int taille_grille = m_hauteur * 0.9;
    int x_grille = m_largeur / 15;
    int y_grille = (m_hauteur - taille_grille) / 2;
    Coordonnees coord_grille(x_grille, y_grille);
    m_grille = new Grille(coord_grille, taille_grille, m_nbLignesCol);

    // Instanciation du score
    int espace_droite_grille = m_largeur - taille_grille - x_grille;
    int largeur_score = (m_largeur - espace_droite_grille) / 3;
    int hauteur_score = m_hauteur / 6;
    int x_score = m_largeur - espace_droite_grille / 2 - largeur_score / 2 - 150;
    int y_score = (m_hauteur - hauteur_score) / 2 - 80;
    Coordonnees coord_score(x_score, y_score);
    m_score = new Score(coord_score, largeur_score, hauteur_score);

    // Initialisation de la grille et attribution du score
    m_grille->initialiserGrille();
    m_grille->setScore(m_score);

    // Création du bouton Relancer
    m_boutonRelancer = new QPushButton("Relancer", this);
    int largeur_bouton = largeur_score;
    int hauteur_bouton = hauteur_score;
    int x_boutonRelancer = x_score;
    int y_boutonRelancer = y_score - hauteur_bouton - 35;
    m_boutonRelancer->setFont(QFont("Arial", 14, QFont::Bold));
    m_boutonRelancer->setGeometry(x_boutonRelancer, y_boutonRelancer, largeur_bouton, hauteur_bouton);
    m_boutonRelancer->setStyleSheet("background-color: #898080; color: white; font-weight: bold;");
    m_boutonRelancer->setFocusPolicy(Qt::NoFocus);
    connect(m_boutonRelancer, &QPushButton::clicked, this, &MainWindow::relancerPartie);

    // Création du bouton "S'identifier / Se connecter"
    QPushButton *m_boutonConnexion = new QPushButton("S'identifier /\nSe connecter", this);
    connect(m_boutonConnexion, &QPushButton::clicked, this, &MainWindow::ouvrirIdentification);
    int x_boutonConnexion = x_score;
    int y_boutonConnexion = y_score + hauteur_score + 35;
    m_boutonConnexion->setFont(QFont("Arial", 14, QFont::Bold));
    m_boutonConnexion->setGeometry(x_boutonConnexion, y_boutonConnexion, largeur_bouton, hauteur_bouton);
    m_boutonConnexion->setStyleSheet("background-color: #898080; color: white; font-weight: bold;");
    m_boutonConnexion->setFocusPolicy(Qt::NoFocus);

    // Création du label pour afficher l'utilisateur connecté
    m_labelUtilisateur = new QLabel(this);
    m_labelUtilisateur->setText("Invité");
    m_labelUtilisateur->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    int largeurLabel = 300;
    int hauteurLabel = 60;
    int x_label = m_largeur - largeurLabel - 30;
    int y_label = 10;
    m_labelUtilisateur->setGeometry(x_label, y_label, largeurLabel, hauteurLabel);
    m_labelUtilisateur->setStyleSheet("font-weight: bold; font-size: 18px; color: black;");
    m_labelUtilisateur->setWordWrap(true);

    // Instanciation du record individuel (affichage identique à Score)
    int x_record = x_boutonConnexion;
    int y_record = y_boutonConnexion + hauteur_bouton + 35;
    Coordonnees coord_record(x_record, y_record);
    if (m_utilisateur && m_utilisateur->obtenirIdentifiant() != "Invité")
        m_record = new Record(coord_record, largeur_score, hauteur_score, m_utilisateur->obtenirMeilleurScore());
    else
        m_record = new Record(coord_record, largeur_score, hauteur_score);

    // Calcul des positions pour le bouton "Taille grille"
    int x_boutonTaille = x_score + largeur_score + 20; // à droite du score
    int y_boutonTaille = y_score + hauteur_score + 35;   // même niveau que le bouton connexion

    // Création du bouton "Taille grille"
    m_boutonTailleGrille = new QPushButton("Taille grille", this);
    m_boutonTailleGrille->setGeometry(x_boutonTaille, y_boutonTaille, largeur_bouton, hauteur_bouton);
    m_boutonTailleGrille->setFont(QFont("Arial", 14, QFont::Bold));
    m_boutonTailleGrille->setStyleSheet("background-color: #898080; color: white; font-weight: bold;");
    m_boutonTailleGrille->setFocusPolicy(Qt::NoFocus);
    connect(m_boutonTailleGrille, &QPushButton::clicked, this, &MainWindow::changerTailleGrille);

    // Positionnement du Record Général sous le bouton "Taille grille" (même espacement de 35 pixels)
    int x_recordGeneral = x_boutonTaille; // aligné avec le bouton "Taille grille"
    int y_recordGeneral = y_boutonTaille + hauteur_bouton + 35;
    Coordonnees coord_recordGeneral(x_recordGeneral, y_recordGeneral);
    m_recordgeneral = new RecordGeneral(coord_recordGeneral, largeur_score, hauteur_score);
    m_recordgeneral->chargerRecordGeneral();

    // Création du bouton "Se déconnecter"
    int x_boutonDeconnexion = x_score + largeur_score + 20; // à droite du score
    int y_boutonDeconnexion = y_score + hauteur_score + 35;   // même niveau que le bouton connexion
    m_boutonDeconnexion = new QPushButton("Se déconnecter", this);
    m_boutonDeconnexion->setGeometry(x_boutonDeconnexion, y_boutonDeconnexion, largeur_bouton, hauteur_bouton);
    m_boutonDeconnexion->setFont(QFont("Arial", 14, QFont::Bold));
    m_boutonDeconnexion->setStyleSheet("background-color: #898080; color: white; font-weight: bold;");
    m_boutonDeconnexion->setFocusPolicy(Qt::NoFocus);
    connect(m_boutonDeconnexion, &QPushButton::clicked, this, &MainWindow::seDeconnecter);

    // Création du bouton "Taille grille"
    x_boutonTaille = x_boutonDeconnexion;
    y_boutonTaille = y_boutonDeconnexion - hauteur_bouton - 35;  // 35 pixels au-dessus du bouton "Se déconnecter"
    m_boutonTailleGrille = new QPushButton("Taille grille", this);
    m_boutonTailleGrille->setGeometry(x_boutonTaille, y_boutonTaille, largeur_bouton, hauteur_bouton);
    m_boutonTailleGrille->setFont(QFont("Arial", 14, QFont::Bold));
    m_boutonTailleGrille->setStyleSheet("background-color: #898080; color: white; font-weight: bold;");
    m_boutonTailleGrille->setFocusPolicy(Qt::NoFocus);
    connect(m_boutonTailleGrille, &QPushButton::clicked, this, &MainWindow::changerTailleGrille);

    // Création du bouton Quitter
    int x_boutonQuitter = x_boutonRelancer + largeur_bouton + 20; // 20 pixels d'espace entre les boutons
    int y_boutonQuitter = y_boutonRelancer; // Même hauteur que le bouton Relancer
    m_boutonQuitter = new QPushButton("Quitter", this);
    m_boutonQuitter->setGeometry(x_boutonQuitter, y_boutonQuitter, largeur_bouton, hauteur_bouton);
    m_boutonQuitter->setFont(QFont("Arial", 14, QFont::Bold));
    m_boutonQuitter->setStyleSheet("background-color: #898080; color: white; font-weight: bold;");
    m_boutonQuitter->setFocusPolicy(Qt::NoFocus);
    connect(m_boutonQuitter, &QPushButton::clicked, this, [this]() {
        // Afficher une boîte de dialogue de confirmation
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir quitter ? Votre progression sur la partie sera perdue.",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            this->close(); // Fermer l'application si l'utilisateur confirme
        }
    });


}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_grille;
    delete m_score;
    delete m_boutonRelancer;
    delete m_boutonQuitter;
}

void MainWindow::paintEvent(QPaintEvent * e) {
    QWidget::paintEvent(e);
    QPainter painter(this);

    // Mettre le fond en blanc
    painter.fillRect(this->rect(), Qt::white);

    int nb_lignes_col = m_grille->getNbLignesCol(); // Taille de la grille en bloc
    m_grille->dessiner(&painter); // Affichage de la grille sans les blocs

    // Affichage des blocs
    for (int i = 0; i < nb_lignes_col; i++) {
        for (int j = 0; j < nb_lignes_col; j++) {
            m_grille->getBloc(i, j)->dessiner(&painter);
        }
    }

    // Affichage du score
    m_score->dessiner(&painter);

    // Affichage du record
    m_record->dessiner(&painter);

    // Affiche du record général
    m_recordgeneral->dessiner(&painter);

    if (m_estFinie) {
        m_grille->afficherPerdu(&painter); // Affichage du message de défaite si la partie est finie
    }

}


void MainWindow::keyPressEvent(QKeyEvent * event) {
    if (!m_estFinie) {
        char direction;
        switch (event->key()) {
        case Qt::Key_Right: direction = 'd'; break;
        case Qt::Key_Left:  direction = 'g'; break;
        case Qt::Key_Up:    direction = 'h'; break;
        case Qt::Key_Down:  direction = 'b'; break;
        default: return;
        }

        m_grille->deplacerBlocs(direction);
        m_estFinie = m_grille->estFinie();

        // Mise à jour du record individuel
        if (m_utilisateur && m_utilisateur->obtenirIdentifiant() != "Invité") {
            int currentScore = m_score->getScore();
            int bestUser = m_utilisateur->obtenirMeilleurScore();
            int nouveauRecord = qMax(bestUser, currentScore);
            m_utilisateur->majMeilleurScore(currentScore);
            m_record->modifierRecord(nouveauRecord);
        } else {
            int nouveauRecord = qMax(m_recordInvite, m_score->getScore());
            m_record->modifierRecord(nouveauRecord);
            m_recordInvite = nouveauRecord;
        }

        // Mise à jour du Record Général uniquement si le joueur est connecté
        if (m_utilisateur && m_utilisateur->obtenirIdentifiant() != "Invité") {
            int globalRecord = m_recordgeneral->getRecordGeneral();
            int currentScore = m_score->getScore();
            // Si le score courant dépasse le record global, on le met à jour
            if (currentScore > globalRecord) {
                m_recordgeneral->modifierRecordGeneral(currentScore, m_utilisateur->obtenirIdentifiant());
                m_recordgeneral->sauvegarderRecordGeneral();
            }
        }

        this->repaint();
    }
}



// Slot qui demande la nouvelle taille de grille (entre 3 et 8)
void MainWindow::changerTailleGrille() {
    bool ok;
    int nbLignes = QInputDialog::getInt(this, "Taille de la grille",
                                        "Entrez le nombre de lignes/colonnes (entre 3 et 8) :",
                                        m_nbLignesCol, 3, 8, 1, &ok);
    if (ok) { // Si la taille choisie est entre 3 et 8
        m_nbLignesCol = nbLignes;
        relancerPartie();
    }
}


void MainWindow::relancerPartie() {
    qDebug() << "relancerPartie appelé";

    // Libérer la mémoire des anciens objets
    delete m_grille;
    m_grille = nullptr; // Réinitialiser le pointeur
    delete m_score;
    m_score = nullptr; // Réinitialiser le pointeur

    // Réinitialiser la grille et le score
    int taille_grille = m_hauteur * 0.9;
    int x_grille = m_largeur / 15;
    int y_grille = (m_hauteur - taille_grille) / 2;
    Coordonnees coord_grille(x_grille, y_grille);
    m_grille = new Grille(coord_grille, taille_grille, m_nbLignesCol);

    int espace_droite_grille = m_largeur - taille_grille - x_grille;
    int largeur_score = (m_largeur - espace_droite_grille) / 3;
    int hauteur_score = m_hauteur / 6;
    int x_score = m_largeur - espace_droite_grille / 2 - largeur_score / 2 - 150;
    int y_score = (m_hauteur - hauteur_score) / 2 - 80;
    Coordonnees coord_score(x_score, y_score);
    m_score = new Score(coord_score, largeur_score, hauteur_score);

    // Réattribuer le score à la grille
    m_grille->setScore(m_score);

    // Réinitialiser l'état de la partie
    m_estFinie = 0;  // Partie en cours

    // Réinitialiser la grille
    m_grille->initialiserGrille();

    // Forcer la mise à jour de l'interface
    this->repaint();
}

void MainWindow::ouvrirIdentification() {
    Identification identDialog(this);
    if (identDialog.exec() == QDialog::Accepted) {
        // Récupérer le nom de l'utilisateur
        QString nomUtilisateur = identDialog.getUsername();
        // Mettre à jour l'objet Utilisateur
        if(m_utilisateur) {
            delete m_utilisateur;
        }
        m_utilisateur = new Utilisateur(nomUtilisateur);
        m_utilisateur->charger();
        m_labelUtilisateur->setText(m_utilisateur->obtenirIdentifiant() + "\nConnecté");

        // Mise à jour immédiate de l'affichage du record pour l'utilisateur connecté
        m_record->modifierRecord(m_utilisateur->obtenirMeilleurScore());
        this->repaint();
    }
}

void MainWindow::seDeconnecter() {
    if (m_utilisateur && m_utilisateur->obtenirIdentifiant() == "Invité") {
        QMessageBox::information(this, "Déconnexion", "Vous n'êtes pas connecté.");
        return;
    }

    // Si l'utilisateur est connecté, le réinitialiser à "Invité"
    delete m_utilisateur;
    m_utilisateur = new Utilisateur("Invité");
    m_labelUtilisateur->setText("Invité");
    QMessageBox::information(this, "Déconnexion", "Vous êtes maintenant déconnecté.");
}













