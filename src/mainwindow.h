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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Accesseurs
    Grille * getGrille(); /* Renvoie le pointeur vers la grille utilisée pour jouer */

    // Mutateurs
    void setGrille(Grille * grille); /* Défini l'attribut m_grille avec un pointeur vers une grille passé en paramètre */

private:
    // Attributs privés
    Ui::MainWindow *ui;
    Grille * m_grille; /* Grille utilisée pour jouer la partie */
    int m_estFinie; /* Vaut 0 si la partie est en cours et 1 si elle est terminée */

    // Overriding
    void paintEvent(QPaintEvent * e); /* Redéfinition de la méthode permettant de dessiner la fenêtre */
    void keyPressEvent(QKeyEvent * event); /* Redéfinition de la méthode permettant de de capter les évènements du clavier */
};



#endif // MAINWINDOW_H
