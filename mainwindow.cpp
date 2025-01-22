#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_grille;
}

Grille * MainWindow::getGrille() {
    return m_grille;
}

void MainWindow::setGrille(Grille * grille) {
    m_grille = grille;
}

void MainWindow::paintEvent(QPaintEvent * e) {
    QWidget::paintEvent(e);
    QPainter painter(this);

    // Mettre le fond en blanc
    painter.fillRect(this->rect(), Qt::white);

    int nb_lignes_col = m_grille->getNbLignesCol();

    m_grille->dessiner(&painter);

    // for (int i = 0; i < nb_lignes_col; i++) {
    //     for (int j = 0; j < nb_lignes_col; j++) {
    //         m_grille->getBloc(i, j)->dessiner(&painter);
    //     }
    // }
}
