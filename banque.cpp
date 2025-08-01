#include <iostream>  // Pour l'entrée/sortie (cin, cout)
#include <iomanip>   // Pour formater le solde (fixed, setprecision)
#include <limits>    // Pour gérer les limites numériques (utilisé pour vider le buffer d'entrée)
#include <string>    // Pour utiliser la classe string

// Utilisation de l'espace de noms standard pour simplifier le code
using namespace std;

// ==========================
// Classe CompteBancaire
// Gère les opérations d'un compte bancaire individuel.
// ==========================
class CompteBancaire {
private:
    string numeroCompte; // Numéro unique du compte
    double solde;        // Solde actuel du compte

public:
    // Constructeur : Initialise un nouveau compte avec un numéro et un solde initial.
    // Le solde initial est optionnel et par défaut à 0.0.
    CompteBancaire(string numero, double montantInitial = 0.0) {
        numeroCompte = numero;
        // Assure que le solde initial n'est jamais négatif
        solde = (montantInitial >= 0) ? montantInitial : 0.0;
        cout << "Compte " << numeroCompte << " créé avec un solde initial de "
             << fixed << setprecision(2) << solde << " USD." << endl;
    }

    // Méthode pour déposer de l'argent sur le compte.
    void deposer(double montant) {
        if (montant > 0) {
            solde += montant;
            cout << "Dépôt de " << fixed << setprecision(2) << montant << " USD effectué." << endl;
        } else {
            cout << "Montant invalide pour un dépôt. Veuillez entrer un montant positif." << endl;
        }
        afficherSolde(); // Affiche le solde après chaque opération
    }

    // Méthode pour retirer de l'argent du compte.
    void retirer(double montant) {
        if (montant <= 0) {
            cout << "Montant invalide pour un retrait. Veuillez entrer un montant positif." << endl;
        } else if (montant > solde) {
            cout << "Fonds insuffisants pour retirer " << fixed << setprecision(2) << montant << " USD." << endl;
        } else {
            solde -= montant;
            cout << "Retrait de " << fixed << setprecision(2) << montant << " USD effectué." << endl;
        }
        afficherSolde(); // Affiche le solde après chaque opération
    }

    // Méthode pour afficher le solde actuel du compte.
    // 'const' indique que cette méthode ne modifie pas l'état de l'objet.
    void afficherSolde() const {
        // Applique le formatage (fixe et 2 décimales) directement à la sortie du solde
        cout << "Solde actuel du compte [" << numeroCompte << "] : "
             << fixed << setprecision(2) << solde << " USD" << endl;
    }

    // Méthode pour obtenir le numéro de compte (utile pour l'affichage ou d'autres vérifications).
    string getNumeroCompte() const {
        return numeroCompte;
    }
};

// ==========================
// Fonction Principale (main)
// Point d'entrée du programme et gestion de l'interaction utilisateur.
// ==========================
int main() {
    string numeroCompteInitial;
    double soldeInitial;
    int choix;
    double montant;

    cout << "--- Bienvenue dans le simulateur de système bancaire! ---" << endl;

    // Demande et validation du numéro de compte
    cout << "Veuillez entrer le numéro de votre compte (ex: 123456789) : ";
    // getline est utilisé pour lire la ligne entière, y compris les espaces, si l'utilisateur en entre
    getline(cin, numeroCompteInitial); 

    // Demande et validation du solde initial
    cout << "Veuillez entrer le solde initial de votre compte : ";
    while (!(cin >> soldeInitial) || soldeInitial < 0) {
        cout << "Solde initial invalide. Veuillez entrer un nombre positif : ";
        cin.clear(); // Efface les indicateurs d'erreur de cin
        // Ignore le reste de la ligne invalide dans le buffer d'entrée
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Création de l'objet CompteBancaire avec les données de l'utilisateur
    CompteBancaire compte(numeroCompteInitial, soldeInitial);

    // Boucle principale du menu interactif
    do {
        cout << "\n--- Menu des Opérations ---" << endl;
        cout << "1. Déposer de l'argent" << endl;
        cout << "2. Retirer de l'argent" << endl;
        cout << "3. Afficher le solde" << endl;
        cout << "4. Quitter" << endl;
        cout << "Entrez votre choix : ";

        // Gère les entrées non numériques pour le choix du menu
        while (!(cin >> choix)) {
            cout << "Choix invalide. Veuillez entrer un chiffre (1-4) : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Nettoie le buffer d'entrée après la lecture d'un entier,
        // avant une possible lecture de ligne suivante ou pour éviter des problèmes
        // si des caractères supplémentaires ont été tapés après l'entier.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Exécute l'action en fonction du choix de l'utilisateur
        switch (choix) {
            case 1: // Déposer
                cout << "Entrez le montant à déposer : ";
                while (!(cin >> montant) || montant <= 0) {
                    cout << "Montant invalide. Veuillez entrer un nombre positif : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                compte.deposer(montant);
                break;
            case 2: // Retirer
                cout << "Entrez le montant à retirer : ";
                while (!(cin >> montant) || montant <= 0) {
                    cout << "Montant invalide. Veuillez entrer un nombre positif : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                compte.retirer(montant);
                break;
            case 3: // Afficher le solde
                compte.afficherSolde();
                break;
            case 4: // Quitter
                cout << "Merci d'avoir utilisé le simulateur bancaire. Au revoir !" << endl;
                break;
            default: // Choix non reconnu
                cout << "Option non reconnue. Veuillez choisir une option entre 1 et 4." << endl;
                break;
        }
    } while (choix != 4); // La boucle continue tant que l'utilisateur ne quitte pas

    return 0; // Fin du programme
}