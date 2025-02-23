#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "grille.h"
#include "identification.h"
#include "utilisateur.h"
#include "record.h"
#include "recordgeneral.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QPushButton> // Ajout pour le bouton
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // Attributs privés
    Ui::MainWindow *ui;
    Grille * m_grille; /* Grille utilisée pour jouer la partie */
    int m_nbLignesCol; /* nombre de lignes/colonnes de la grille (valeur entre 3 et 8) */
    Score * m_score; /* Pointeur vers le score de la partie */
    int m_largeur; /* Largeur de la fenêtre */
    int m_hauteur; /* Hauteur de la fenêtre */
    int m_estFinie; /* Vaut 0 si la partie est en cours et 1 si elle est terminée */
    int m_recordInvite; /* Pointeur vers le record de l'utilisateur avant connexion (Invité) */
    Record *  m_record; /* Pointeur vers le record de l'utilisateur une fois connecté */
    RecordGeneral * m_recordgeneral; /* Pointeur vers le record global des utilisateurs qui ont un compte */
    Utilisateur *m_utilisateur; /* Pointeur vers l'utilisateur connecté */
    QLabel *m_labelUtilisateur; /* Pointeur vers le nom de l'utilisateur en haut à droite de l'écran */
    QPushButton *m_boutonRecord; /* Bouton record de l'utilisateur */
    QPushButton *m_boutonRecordGeneral; /* Bouton record global de tous les utilisateurs qui ont un compte */
    QPushButton *m_boutonRelancer; /* Bouton pour relancer une partie */
    QPushButton *m_boutonTailleGrille; /* Bouton pour choisir la taille de la grille */
    QPushButton *m_boutonDeconnexion; /* Bouton pour se déconnecter */
    QPushButton *m_boutonQuitter; /* Bouton pour quitter le jeu */


    // Méthodes publiques
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Overriding
    void paintEvent(QPaintEvent * e); /* Redéfinition de la méthode permettant de dessiner la fenêtre */
    void keyPressEvent(QKeyEvent * event); /* Redéfinition de la méthode permettant de capter les évènements du clavier */

private slots:
    // Slot qui demande la nouvelle taille de grille (entre 3 et 8)
    void changerTailleGrille() ;
    void relancerPartie(); /* Slot pour gérer le clic du bouton Relancer */
public slots :
    void ouvrirIdentification(); /* Slot pour gérer le clic du bouton S'identifier / Se connecter */
    void seDeconnecter();  /* Slot pour gérer le clic du bouton Se déconnecter */

};

#endif // MAINWINDOW_H
