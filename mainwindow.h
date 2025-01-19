#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include "grille.h"
#include <QMainWindow>

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
    Grille * getGrille();

    // Mutateurs
    void setGrille(Grille * grille);

private:
    Ui::MainWindow *ui;
    Grille * m_grille;
    void paintEvent(QPaintEvent * e);
};
#endif // MAINWINDOW_H
