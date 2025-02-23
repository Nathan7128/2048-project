#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include "grille.h"
#include <QMainWindow>
#include <QKeyEvent>

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
    Score * m_score; /* Pointeur vers le score de la partie */
    int m_largeur; /* Largeur de la fenêtre */
    int m_hauteur; /* Hauteur de la fenêtre */
    int m_estFinie; /* Vaut 0 si la partie est en cours et 1 si elle est terminée.
        La partie est finie si la grille est remplie et le joueur ne peut plus effectuer de déplacement, il n'est pas possible de gagner une partie */

    // Méthodes publiques
public:
    MainWindow(QWidget *parent = nullptr); /* Constructeur par défaut */
    MainWindow(const MainWindow& m); /* Constructeur de recopie */
    ~MainWindow();

    // Overriding
    void paintEvent(QPaintEvent * e); /* Redéfinition de la méthode permettant de dessiner la fenêtre */
    void keyPressEvent(QKeyEvent * event); /* Redéfinition de la méthode permettant de de capter les évènements du clavier */

    // Surcharge des opérateurs
    MainWindow& operator=(const MainWindow& m); /* Surcharge de l'opérateur =" */
};



#endif // MAINWINDOW_H
