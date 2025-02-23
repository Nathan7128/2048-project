#ifndef _IDENTIFICATION_H_
#define _IDENTIFICATION_H_

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;
class QRadioButton;

class Identification : public QDialog {
    Q_OBJECT
public:
    explicit Identification(QWidget *parent = nullptr);
    // Accesseurs pour récupérer l'état de connexion et les infos de l'utilisateur
    bool isConnected() const { return m_isConnected; }
    QString getUsername() const { return m_username; }
    int getBestScore() const { return m_bestScore; }
    // Met à jour le score maximum si newScore est supérieur
    void updateBestScore(int newScore);

private slots:
    void onModeChanged();
    void onSubmit();

private:
    void setupUI();
    void processInscription();
    void processConnexion();

    // Widgets de l'interface
    QRadioButton *m_radioInscription;
    QRadioButton *m_radioConnexion;
    QLineEdit *m_lineEditUsername;
    QLineEdit *m_lineEditPassword;
    QLineEdit *m_lineEditConfirm; // Utilisé uniquement pour l'inscription
    QPushButton *m_submitButton;
    QLabel *m_labelMessage;

    // Variables d'état
    bool m_isConnected;
    QString m_username;
    int m_bestScore;
};

#endif // IDENTIFICATION_H
