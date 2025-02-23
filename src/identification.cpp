#include "identification.h"

#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

Identification::Identification(QWidget *parent)
    : QDialog(parent),
    m_isConnected(false),
    m_bestScore(0)
{
    setupUI();
}

void Identification::setupUI() {
    // Création des widgets
    m_radioInscription = new QRadioButton("S'inscrire", this);
    m_radioConnexion = new QRadioButton("Se connecter", this);
    m_radioInscription->setChecked(true); // mode inscription par défaut

    m_lineEditUsername = new QLineEdit(this);
    m_lineEditPassword = new QLineEdit(this);
    m_lineEditPassword->setEchoMode(QLineEdit::Password);
    m_lineEditConfirm = new QLineEdit(this);
    m_lineEditConfirm->setEchoMode(QLineEdit::Password);

    m_submitButton = new QPushButton("Valider", this);
    m_labelMessage = new QLabel("", this);

    // Organisation dans des layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *radioLayout = new QHBoxLayout();
    radioLayout->addWidget(m_radioInscription);
    radioLayout->addWidget(m_radioConnexion);
    mainLayout->addLayout(radioLayout);

    mainLayout->addWidget(new QLabel("Identifiant :", this));
    mainLayout->addWidget(m_lineEditUsername);
    mainLayout->addWidget(new QLabel("Mot de passe :", this));
    mainLayout->addWidget(m_lineEditPassword);
    mainLayout->addWidget(new QLabel("Confirmer le mot de passe :", this));
    mainLayout->addWidget(m_lineEditConfirm);

    mainLayout->addWidget(m_submitButton);
    mainLayout->addWidget(m_labelMessage);

    setLayout(mainLayout);
    setWindowTitle("Identification");

    // Connexions
    connect(m_radioInscription, &QRadioButton::toggled, this, &Identification::onModeChanged);
    connect(m_submitButton, &QPushButton::clicked, this, &Identification::onSubmit);

    // Ajustement de l'interface selon le mode
    onModeChanged();
}

void Identification::onModeChanged() {
    if (m_radioInscription->isChecked()) {
        m_lineEditConfirm->setEnabled(true);
    } else {
        m_lineEditConfirm->setEnabled(false);
    }
    m_labelMessage->clear();
}

void Identification::onSubmit() {
    if (m_radioInscription->isChecked()) {
        processInscription();
    } else {
        processConnexion();
    }
}

void Identification::processInscription() {
    QString username = m_lineEditUsername->text().trimmed();
    QString password = m_lineEditPassword->text();
    QString confirm = m_lineEditConfirm->text();

    // Empêcher que l'identifiant soit "Invité"
    if (username.compare("Invité", Qt::CaseInsensitive) == 0) {
        m_labelMessage->setText("L'identifiant 'Invité' est réservé.");
        return;
    }

    if (username.isEmpty() || password.isEmpty() || confirm.isEmpty()) {
        m_labelMessage->setText("Veuillez remplir tous les champs.");
        return;
    }
    if (password != confirm) {
        m_labelMessage->setText("Les mots de passe ne correspondent pas.");
        return;
    }
    // Créer le dossier "identifiants" s'il n'existe pas
    QDir dir;
    if (!dir.exists("identifiants"))
        dir.mkdir("identifiants");

    // Vérifier si l'identifiant est déjà pris (fichier existant dans le dossier "identifiants")
    QString filename = "identifiants/" + username + ".txt";
    QFile file(filename);
    if (file.exists()) {
        m_labelMessage->setText("Identifiant déjà pris.");
        return;
    }
    // Création du fichier avec le mot de passe et un score initial de 0 (première ligne : mdp, deuxième ligne : score)
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << password << "\n" << "0" << "\n";
        file.close();
        m_labelMessage->setText("Inscription réussie.");
        QMessageBox::information(this, "Inscription", "Inscription réussie !");
        m_isConnected = true;
        m_username = username;
        m_bestScore = 0;
        accept(); // Ferme le dialogue avec un résultat accepté
    } else {
        m_labelMessage->setText("Erreur lors de la création du fichier.");
        QMessageBox::critical(this, "Erreur", "Erreur lors de la création du fichier.");
    }
}

void Identification::processConnexion() {
    QString username = m_lineEditUsername->text().trimmed();
    QString password = m_lineEditPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        m_labelMessage->setText("Veuillez remplir tous les champs.");
        return;
    }
    // Chemin du fichier dans le dossier "identifiants"
    QString filename = "identifiants/" + username + ".txt";
    QFile file(filename);
    if (!file.exists()) {
        m_labelMessage->setText("Identifiant non existant.");
        QMessageBox::warning(this, "Connexion", "Identifiant non existant.");
        return;
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString storedPassword = in.readLine();
        if (storedPassword == password) {
            m_isConnected = true;
            m_username = username;
            // Lecture du meilleur score (deuxième ligne)
            QString scoreLine = in.readLine();
            m_bestScore = scoreLine.toInt();
            m_labelMessage->setText("Connexion réussie.");
            QMessageBox::information(this, "Connexion", "Connexion réussie !");
            file.close();
            accept(); // Ferme le dialogue avec un résultat accepté
        } else {
            m_labelMessage->setText("Mot de passe incorrect.");
            QMessageBox::warning(this, "Connexion", "Mot de passe incorrect.");
            file.close();
        }
    } else {
        m_labelMessage->setText("Erreur lors de l'ouverture du fichier.");
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ouverture du fichier.");
    }
}

void Identification::updateBestScore(int newScore) {
    // Vérifier que l'utilisateur est connecté
    if (m_username.isEmpty())
        return;

    // Chemin complet du fichier dans le dossier "identifiants"
    QString filename = "identifiants/" + m_username + ".txt";
    QFile file(filename);
    if (!file.exists())
        return;

    // Lire le fichier existant
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString storedPassword = in.readLine();    // première ligne : mot de passe
    QString bestScoreStr = in.readLine();        // deuxième ligne : score max
    int bestScore = bestScoreStr.toInt();
    QStringList autresLignes;
    while (!in.atEnd()) {
        autresLignes << in.readLine();
    }
    file.close();

    // Si le nouveau score est supérieur, on met à jour le fichier
    if (newScore > bestScore) {
        m_bestScore = newScore;
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << storedPassword << "\n" << newScore << "\n";
            // Réécrire les autres informations (par exemple les parties sauvegardées)
            for (const QString &ligne : autresLignes) {
                out << ligne << "\n";
            }
            file.close();
        }
    }
}
