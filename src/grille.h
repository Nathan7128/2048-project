#ifndef _GRILLE_H_
#define _GRILLE_H_



#include "blocnumerote.h"
#include "blocnul.h"
#include "blocbonus.h"
#include "blocmalus.h"
#include <string.h>
#include "score.h"

using namespace std;



// Classe permettant de modéliser la grille du 2048.
// Cette grille possède le même nombre de lignes et de colonnes, et chaque case de cette dernière est composée d'un bloc
class Grille {
    // Attributs protégés
protected :
    Bloc*** m_matBlocs; /* Matrice de pointeurs vers des objets de type "Bloc" : cette matrice correspond à la grille */
    int m_nbBlocs; /* Nombre de blocs non nuls dans la grille à un instant t (nombre de cases non vides) */
    Coordonnees m_coord; /* Coordonnées x (abscisse) et y (ordonnée) de la grille exprimées en pixel */
    int m_taille; /* Largeur et hauteur de la grille en pixel (la grille est un carré). Par taille, on entend la longueur en pixel entre le
            l'extérieur du contour gauche de la grille et l'extérieur du bord droit de la grille (ou du bord bas et du bord haut) */
    int m_nbLignesCol; /* Nombre de lignes et de colonnes de la grille : si m_nbLignesCol = 4, alors la grille est de taille 4x4 */
    int m_tailleBlocs; /* Taille de tous les blocs de la grille (ils font tous la même taille)
            La taille du bloc correspond à sa largeur et à sa hauteur */
    int m_epContours; /* Epaisseur du crayon utilisé pour tracer les contours extérieurs et intérieurs de la grille.
            Les contours intérieurs correspondent aux traits de séparation entre les différents blocs */
    Score* m_score; /* Pointeur vers un objet de type Score correspondant au score en cours de la partie */

    // Déclaration des méthodes
public :
    Grille(Coordonnees coord = Coordonnees(), int taille = 120, int nbLignesCol = 4); /* Constructeur par défaut */
    Grille(const Grille& grille); /* Constructeur de recopie */
    ~Grille(); /* Destructeur */

    // Surcharge des opérateurs
    Grille& operator=(const Grille& g);

    // Accesseurs
    Bloc * getBloc(int i, int j); /* Renvoie le pointeur de bloc contenu dans la case située à la ligne i et la colonne j */
    int getNbBlocs(); /* Renvoie le nombre de blocs numérotés actuellement présents dans la grille */
    int getNbLignesCol();

    // Mutateurs
    void setBloc(int i, int j, Bloc * bloc); /* Place un bloc à la ligne i et la colonne j de la grille */
    void setScore(Score * score);

    Coordonnees convertirCoordBloc(int i, int j); /* Permet de convertir des coordonnées d'un bloc exprimées en ligne et colonne en coordonnées
            exprimées en pixel */

    void nouveauBlocNum(); /* Place un nouveau bloc numéroté dans la grille avec une valeur aléatoirement choisie parmi 2 et 4 (avec des probabilités
            respectivement égales à 3/4 et 1/4. Lorsqu'on créé un nouveau bloc numéroté, il est placé aléatoirement.
            On va donc déterminer dans cette méthode la case ou va se trouver ce nouveau bloc */

    void nouveauBlocBonus();  /* Place un nouveau bloc bonus dans la grille avec une valeur aléatoirement choisie parmi 2, 4 et 8 (avec des probabilités
            respectivement égales à 8/12 (2/3), 1/4 (3/12) et 1/12. Lorsqu'on créé un nouveau bloc bonus, il est placé aléatoirement.
            On va donc déterminer dans cette méthode la case ou va se trouver ce nouveau bloc */

    void nouveauBlocMalus();  /* Place un nouveau bloc malus dans la grille avec une valeur aléatoirement choisie parmi 2, 4 et 8 (avec des probabilités
            respectivement égales à 8/12 (2/3), 1/4 (3/12) et 1/12. Lorsqu'on créé un nouveau bloc malus, il est placé aléatoirement.
            On va donc déterminer dans cette méthode la case ou va se trouver ce nouveau bloc */

    void initialiserGrille(); /* Initialise la grille en la remplissant de blocs nuls et de 2 blocs numérotés placés aléatoirement dans la grille */

    void transfererBloc(int i_old, int j_old, int i_new, int j_new); /* Déplace un bloc numéroté situé à la ligne i et la colonne j de la grille
            jusqu'à la ligne i_new et la colonne j_new de la grille. Le déplacement est effectué dans le cas ou le bloc est déplacé jusqu'à un bord ou
            jusqu'au prochain bloc numéroté qui lui bloque le déplacement (avec lequel il ne peut pas fusionner) */

    void fusionnerBlocs(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus); /* Fusionne 2 blocs numérotés de la grille.
            Une fusion est le fait de déplacer un bloc numéroté vers un autre bloc numéroté qui possède la même valeur, et ainsi
            obtenir un nouveau bloc numéroté d'une valeur égale à deux fois la valeur des blocs à fusionner.
            Les entiers "i_bloc_depl" et "j_bloc_depl" correspondent à la ligne et la colonne de la case qui contient le pointeur vers le
            bloc à déplacer. Après avoir déplacé et fusionné ce bloc, on va placer un pointeur vers un bloc nul dans la case qui le
            contenait.
            Les entiers "i_bloc_fus" et "j_bloc_fus" correspondent à la ligne et la colonne de la case qui contient le pointeur vers le
            bloc qui va être fusionné avec le bloc à déplacer. Ce bloc sera donc remplacé par le bloc résultant de la fusion réalisée. */

    // Fusion entre deux blocs numérotés
    void fusionnerBlocsNumeroteNumerote(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus, char direction);

    // Fusion entre un bloc numéroté et un bloc bonus
    void fusionnerBlocsNumeroteBonus(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus,  char direction);

    // Fusion entre un bloc bonus et un bloc numéroté
    void fusionnerBlocsBonusNumerote(int i_bloc_bonus, int j_bloc_bonus, int i_bloc_numero, int j_bloc_numero,  char direction);

    // Fusion entre un bloc numéroté et un bloc malus
    void fusionnerBlocsNumeroteMalus(int i_bloc_depl, int j_bloc_depl, int i_bloc_fus, int j_bloc_fus, char direction);

     // Fusion entre un malus et un bloc numéroté
    void fusionnerBlocsMalusNumerote(int i_bloc_malus, int j_bloc_malus, int i_bloc_numero, int j_bloc_numero, char direction);

    // Fusion entre deux blocs bonus
    void fusionnerBlocsBonusBonus(int i_bloc_bonus1, int j_bloc_bonus1, int i_bloc_bonus2, int j_bloc_bonus2,  char direction);

    // Fusion entre deux blocs malus
    void fusionnerBlocsMalusMalus(int i_bloc_malus1, int j_bloc_malus1, int i_bloc_malus2, int j_bloc_malus2, char direction);

    // Fusion entre un bloc bonus et un bloc malus
    void fusionnerBlocsBonusMalus(int i_bloc_bonus, int j_bloc_bonus, int i_bloc_malus, int j_bloc_malus,  char direction);


    bool deplacerBloc(int i, int j, char direction, bool test_finie = false); /* Déplace un bloc numéroté situé à la ligne i et la colonne j de la
            grille dans une direction. Retourne true si le bloc a été déplacé été false sinon.
            Le paramètre "test_finie" permet d'indiquer si on utilise la méthode pour réellement déplacer un bloc ou pour savoir si le bloc est
            déplaçable. En effet, lorsqu'on souhaitera tester si la partie est finie (s'il n'y a plus de déplacement possible), on voudra essayer de
            déplacer chaque bloc dans chaque direction, sans pour autont effectuer le déplacement. Ce paramètre vaut false si on souhaite réellement
            déplacer le bloc, et true si on veut juste tester si le bloc est déplaçable. */

    bool deplacerBlocs(char direction, bool test_finie = false); /* Permet de déplacer (ou non s'ils sont bloqués) l'ensemble des blocs numérotés dans
            une direction saisie grâce aux 4 touches fléchées du clavier.
            Lorsqu'on effectue un déplacement, on n'essaye pas de déplacer les blocs qui sont sur le bord de la grille car ils sont bloqués (par le
            bord de la grille) et ne pourrons pas être déplacés dans tous les cas. Par exemple, si on déplace les blocs vers la droite, on n'essaiera
            pas de déplacer les blocs de la colonne la plus à droite.
            Cette méthode retourne true si au moins un bloc a été déplacé et false sinon.
            Le paramètre test_finie vaut true uniquement si cette méthode "déplacerBlocs" est appelée par la méthode "est_finie" (si on souhaite savoir si
            la partie est terminée) */

    bool estFinie(); /* Retourne true si le partie est terminée et false si il y a encore des déplacements possibles. On vérifie si la partie est finie
            à chaque tour ou la grille est remplie de blocs numérotés, c'est à dire à chaque tour ou m_nbBlocs = m_taille*m_taille */

    void marquerNonFusionnable(int i, int j, char direction);

    void dessiner(QPainter *p); /* Dessine la grille, c'est à dire tous les contours des blocs. Tous les contours ont la même épaisseur, que ce soit
            ceux sur les bords ou ceux à l'intérieur (qui séparent les blocs) */

    void afficherPerdu(QPainter *p); /* Affiche le message de fin quand la partie est perdue */
};



#endif // !_GRILLE_H_
