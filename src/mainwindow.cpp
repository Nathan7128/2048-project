#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_estFinie = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_grille;
}

void MainWindow::setGrille(Grille * grille) {
    m_grille = grille;
}

void MainWindow::setScore(Score * score) {
    m_score = score;
}

void MainWindow::paintEvent(QPaintEvent * e) {
    QWidget::paintEvent(e);
    QPainter painter(this);

    // Mettre le fond en blanc
    painter.fillRect(this->rect(), Qt::white);

    int nb_lignes_col = m_grille->getNbLignesCol();

    m_grille->dessiner(&painter);

    for (int i = 0; i < nb_lignes_col; i++) {
        for (int j = 0; j < nb_lignes_col; j++) {
            m_grille->getBloc(i, j)->dessiner(&painter);
        }
    }

    m_score->dessiner(&painter);

    m_estFinie = m_grille->estFinie();

    if (m_estFinie) {
        m_grille->afficherPerdu(&painter);
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

        this->repaint();
    }
}






