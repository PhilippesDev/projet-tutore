#include <iostream>     // pour std::cout et std::cin
#include <cstdlib>      // pour rand() et srand()
#include <ctime>        // pour time()

using namespace std;

// Fonction pour obtenir le choix en texte
string choixEnTexte(int choix) {
    switch (choix) {
        case 1: return "Pierre";
        case 2: return "Feuille";
        case 3: return "Ciseaux";
        default: return "Inconnu";
    }
}

int main() {
    int joueur, ordinateur;
    char rejouer = 'o';

    srand(time(0));  // Initialisation du générateur aléatoire

    while (rejouer == 'o' || rejouer == 'O') {
        // Affichage des options
        cout << "Choisissez :\n";
        cout << "1. Pierre\n2. Feuille\n3. Ciseaux\n";
        cout << "Votre choix (1-3) : ";
        cin >> joueur;

        // Vérifier l’entrée de l’utilisateur
        if (joueur < 1 || joueur > 3) {
            cout << "Choix invalide. Reessayez.\n";
            continue;
        }

        // Choix de l'ordinateur aléatoirement
        ordinateur = rand() % 3 + 1;

        // Affichage des choix
        cout << "Vous avez choisi : " << choixEnTexte(joueur) << endl;
        cout << "L'ordinateur a choisi : " << choixEnTexte(ordinateur) << endl;

        // Détermination du résultat
        if (joueur == ordinateur) {
            cout << "Egalite !\n";
        } else if (
            (joueur == 1 && ordinateur == 3) ||
            (joueur == 2 && ordinateur == 1) ||
            (joueur == 3 && ordinateur == 2)
        ) {
            cout << " Vous avez gagne !\n";
        } else {
            cout << "L'ordinateur a gagne.\n";
        }

        // Demander à rejouer
        cout << "\nVoulez-vous rejouer ? (o/n) : ";
        cin >> rejouer;
        cout << "\n-------------------------\n";
    }

    cout << "Merci d'avoir joue ! A bientot.\n";
    return 0;
}
