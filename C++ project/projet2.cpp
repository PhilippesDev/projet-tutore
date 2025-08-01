#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Définition de la classe Contact
class Contact {
public:
    string nom;
    string telephone;
    string email;

    Contact(string n, string t, string e) {
        nom = n;
        telephone = t;
        email = e;
    }

    void afficher() {
        cout << "Nom: " << nom << ", Telephone: " << telephone << ", Email: " << email << endl;
    }
};

// Fonction pour afficher le menu
void afficherMenu() {
    cout << "\n===== MENU =====" << endl;
    cout << "1. Ajouter un contact" << endl;
    cout << "2. Afficher tous les contacts" << endl;
    cout << "3. Rechercher un contact par nom" << endl;
    cout << "4. Supprimer un contact par nom" << endl;
    cout << "5. Quitter" << endl;
    cout << "Votre choix: ";
}

int main() {
    vector<Contact> contacts;
    int choix;
    string nom, telephone, email;

    do {
        afficherMenu();
        cin >> choix;
        cin.ignore();  // Pour vider le buffer après cin

        switch (choix) {
            case 1:
                cout << "Nom: ";
                getline(cin, nom);
                cout << "Telephone: ";
                getline(cin, telephone);
                cout << "Email: ";
                getline(cin, email);
                contacts.push_back(Contact(nom, telephone, email));
                cout << "Contact ajoute.\n";
                break;

            case 2:
                if (contacts.empty()) {
                    cout << "Aucun contact a afficher.\n";
                } else {
                    cout << "\nListe des contacts:\n";
                    for (Contact c : contacts) {
                        c.afficher();
                    }
                }
                break;

            case 3: {
                cout << "Entrez le nom a rechercher: ";
                getline(cin, nom);
                bool trouve = false;
                for (Contact c : contacts) {
                    if (c.nom == nom) {
                        cout << "Contact trouve: ";
                        c.afficher();
                        trouve = true;
                        break;
                    }
                }
                if (!trouve) cout << "Contact non trouve.\n";
                break;
            }

            case 4: {
                cout << "Entrez le nom a supprimer: ";
                getline(cin, nom);
                bool supprime = false;
                for (auto it = contacts.begin(); it != contacts.end(); ++it) {
                    if (it->nom == nom) {
                        contacts.erase(it);
                        cout << "Contact supprime.\n";
                        supprime = true;
                        break;
                    }
                }
                if (!supprime) cout << "Contact non trouve !!!\n";
                break;
            }

            case 5:
                cout << "Au revoir !\n";
                break;

            default:
                cout << "Choix invalide. Reessayez.\n";
        }

    } while (choix != 5);

    return 0;
}
