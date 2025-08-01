#include <iostream>
#include <iomanip>  // pour formater le solde
using namespace std;

// ==========================
// Classe CompteBancaire
// ==========================
class CompteBancaire {
private:
    string numeroCompte;
    double solde;

public:
    // Constructeur
    CompteBancaire(string numero, double montantInitial = 0.0) {
        numeroCompte = numero;
        solde = montantInitial;
    }

    // Deposer de l'argent
    void deposer(double montant) {
        if (montant > 0) {
            solde += montant;
            cout << "Depot de " << montant << " effectue." << endl;
        } else {
            cout << "Montant invalide pour un depot." << endl;
        }
    }

    // Retirer de l'argent
    void retirer(double montant) {
        if (montant > solde) {
            cout << "Fonds insuffisants pour retirer " << montant << "." << endl;
        } else if (montant <= 0) {
            cout << "Montant invalide pour un retrait." << endl;
        } else {
            solde -= montant;
            cout << "Retrait de " << montant << " effectue." << endl;
        }
    }

    // Afficher le solde
    void afficherSolde() const {
        cout << fixed << setprecision(2);  // format : 2 chiffres apres la virgule
        cout << "Solde du compte [" << numeroCompte << "] : " << solde << " USD" << endl;
    }
};

// ==========================
// Fonction principale
// ==========================
int main() {
    // Creation du compte
    CompteBancaire compte("00123456789", 1000.0); // solde initial

    // Operations
    compte.afficherSolde();
    compte.deposer(250.75);
    compte.retirer(100.50);
    compte.retirer(2000);  // test : retrait trop eleve
    compte.afficherSolde();

    return 0;
}

