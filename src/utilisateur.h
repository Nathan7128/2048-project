#ifndef UTILISATEUR_HPP
#define UTILISATEUR_HPP

#include <QString>

class Utilisateur {
public:
    // Constructeur : on fournit l'identifiant de l'utilisateur.
    explicit Utilisateur(const QString &identifiant);

    // Charge les informations depuis le fichier "identifiants/<identifiant>.txt"
    // Retourne true si le chargement a réussi, false sinon.
    bool charger();

    // Sauvegarde les informations dans le fichier (écrit le mot de passe, le meilleur score et éventuellement d'autres données).
    // Retourne true si la sauvegarde a réussi.
    bool sauvegarder();

    // Met à jour le meilleur score si nouveauScore est supérieur à l'actuel, puis sauvegarde le fichier.
    void majMeilleurScore(int nouveauScore);

    // Accesseurs
    QString obtenirIdentifiant() const;
    int obtenirMeilleurScore() const;
    QString obtenirMotDePasse() const;

private:
    QString m_identifiant;
    QString m_motDePasse;
    int m_meilleurScore;

    // Chemin complet vers le fichier utilisateur (dans le dossier "identifiants")
    QString m_cheminFichier;
};

#endif // UTILISATEUR_HPP
