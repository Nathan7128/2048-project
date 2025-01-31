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
    int m_estFinie; /* Vaut 0 si la partie est en cours et 1 si elle est terminée */

    // Méthodes publiques
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Overriding
    void paintEvent(QPaintEvent * e); /* Redéfinition de la méthode permettant de dessiner la fenêtre */
    void keyPressEvent(QKeyEvent * event); /* Redéfinition de la méthode permettant de de capter les évènements du clavier */
};



#endif // MAINWINDOW_H
