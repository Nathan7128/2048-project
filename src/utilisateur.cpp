#include "Utilisateur.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

Utilisateur::Utilisateur(const QString &identifiant)
    : m_identifiant(identifiant), m_meilleurScore(0)
{
    // Définir le chemin du fichier de l'utilisateur dans le dossier "identifiants"
    m_cheminFichier = "identifiants/" + m_identifiant + ".txt";
}

bool Utilisateur::charger() {
    QFile fichier(m_cheminFichier);
    if (!fichier.exists())
        return false;
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&fichier);
    // Première ligne : mot de passe
    m_motDePasse = in.readLine();
    // Deuxième ligne : meilleur score
    QString scoreStr = in.readLine();
    m_meilleurScore = scoreStr.toInt();

    fichier.close();
    return true;
}

bool Utilisateur::sauvegarder() {
    // S'assurer que le dossier "identifiants" existe, sinon le créer
    QDir dossier;
    if (!dossier.exists("identifiants"))
        dossier.mkdir("identifiants");

    QFile fichier(m_cheminFichier);
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&fichier);
    // Écriture du mot de passe et du meilleur score (puis éventuellement d'autres données)
    out << m_motDePasse << "\n" << m_meilleurScore << "\n";
    fichier.close();
    return true;
}

void Utilisateur::majMeilleurScore(int nouveauScore) {
    if (m_identifiant == "Invité")
        return; // Ne met pas à jour le fichier pour l'invité

    if (nouveauScore > m_meilleurScore) {
        m_meilleurScore = nouveauScore;
        sauvegarder(); // Mise à jour du fichier avec le nouveau score
    }
}


QString Utilisateur::obtenirIdentifiant() const {
    return m_identifiant;
}

int Utilisateur::obtenirMeilleurScore() const {
    return m_meilleurScore;
}

QString Utilisateur::obtenirMotDePasse() const {
    return m_motDePasse;
}
