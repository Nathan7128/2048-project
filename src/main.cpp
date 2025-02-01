#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Initialisation de la graine du générateur de nombres aléatoires
    srand(static_cast<unsigned int>(std::time(nullptr)));

    try {
        // Instanciation de l'application et de la fenêtre
        QApplication a(argc, argv);
        MainWindow w;

        // Affichage de la fenêtre
        w.show();

        // Exécution de l'application
        return a.exec();
    }
    catch (ExceptionCoordNeg& ex) {
        cerr << ex.m_message << endl;
    }
    catch (ExceptionLigneCol& ex) {
        cerr << ex.m_message << endl;
    }
    catch (ExceptionValeurBloc& ex) {
        cerr << ex.m_message << endl;
    }
    catch (ExceptionGrillePleine& ex) {
        cerr << ex.m_message << endl;
    }
    catch (ExceptionNbLignesCol& ex) {
        cerr << ex.m_message << endl;
    }
    catch (ExceptionTailleObjet& ex) {
        cerr << ex.m_message << endl;
    }
}
