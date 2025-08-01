#include <iostream>  // Pour cin, cout, endl
#include <vector>    // Pour std::vector
#include <stdexcept> // Pour std::invalid_argument, std::out_of_range, std::runtime_error
#include <limits>    // NOUVELLE LIGNE : Pour std::numeric_limits, utilisé dans la gestion des erreurs de saisie

// Déclaration anticipée de la classe Matrice pour que la fonction friend puisse la référencer
template <typename T>
class Matrice;

// Déclaration anticipée de la surcharge de l'opérateur <<
// C'est une fonction template qui doit être déclarée avant son utilisation comme friend
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrice<T>& mat);

template <typename T>
class Matrice {
private:
    int lignes_;
    int colonnes_;
    std::vector<std::vector<T>> data_;

public:
    // Constructeur
    Matrice(int lignes, int colonnes) : lignes_(lignes), colonnes_(colonnes) {
        if (lignes <= 0 || colonnes <= 0) {
            throw std::invalid_argument("Les dimensions de la matrice doivent être positives.");
        }
        data_.resize(lignes_); // Redimensionne le vecteur externe (lignes)
        for (int i = 0; i < lignes_; ++i) {
            data_[i].resize(colonnes_); // Redimensionne chaque vecteur interne (colonnes)
        }
    }

    // Accesseur pour les lignes
    int getLignes() const {
        return lignes_;
    }

    // Accesseur pour les colonnes
    int getColonnes() const {
        return colonnes_;
    }

    // Accès à un élément (lecture)
    T getElement(int row, int col) const {
        if (row < 0 || row >= lignes_ || col < 0 || col >= colonnes_) {
            throw std::out_of_range("Indices de matrice hors limites (getElement).");
        }
        return data_[row][col];
    }

    // Modification d'un élément
    void setElement(int row, int col, T value) {
        if (row < 0 || row >= lignes_ || col < 0 || col >= colonnes_) {
            throw std::out_of_range("Indices de matrice hors limites (setElement).");
        }
        data_[row][col] = value;
    }

    // Surcharge de l'opérateur + pour l'addition de matrices
    Matrice<T> operator+(const Matrice<T>& autreMatrice) const {
        if (lignes_ != autreMatrice.lignes_ || colonnes_ != autreMatrice.colonnes_) {
            throw std::runtime_error("Les matrices doivent avoir les mêmes dimensions pour l'addition.");
        }

        Matrice<T> resultat(lignes_, colonnes_); // Crée une nouvelle matrice pour le résultat
        for (int i = 0; i < lignes_; ++i) {
            for (int j = 0; j < colonnes_; ++j) {
                resultat.data_[i][j] = data_[i][j] + autreMatrice.data_[i][j];
            }
        }
        return resultat;
    }

    // Déclaration de la fonction amie pour la surcharge de l'opérateur <<
    // Notez la syntaxe "operator<<<T>" pour les fonctions template friend
    friend std::ostream& operator<<<T>(std::ostream& os, const Matrice<T>& mat);
};

// Implémentation de la surcharge de l'opérateur <<
// Doit être en dehors de la classe et utiliser le template
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrice<T>& mat) {
    for (int i = 0; i < mat.lignes_; ++i) {
        for (int j = 0; j < mat.colonnes_; ++j) {
            os << mat.data_[i][j] << "\t"; // Utilise une tabulation pour l'alignement
        }
        os << std::endl; // Nouvelle ligne pour chaque ligne de la matrice
    }
    return os;
}

// Fonction utilitaire pour demander les dimensions et les éléments d'une matrice à l'utilisateur
template <typename T>
Matrice<T> demanderMatrice(const std::string& nom) {
    int lignes, colonnes;
    std::cout << "--- Saisie de la Matrice " << nom << " ---" << std::endl;
    std::cout << "Entrez le nombre de lignes : ";
    // Boucle de validation pour les lignes
    while (!(std::cin >> lignes) || lignes <= 0) {
        std::cout << "Saisie invalide. Entrez un nombre entier positif pour les lignes : ";
        std::cin.clear(); // Réinitialise l'état d'erreur du flux
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore le reste de la ligne invalide
    }
    std::cout << "Entrez le nombre de colonnes : ";
    // Boucle de validation pour les colonnes
    while (!(std::cin >> colonnes) || colonnes <= 0) {
        std::cout << "Saisie invalide. Entrez un nombre entier positif pour les colonnes : ";
        std::cin.clear(); // Réinitialise l'état d'erreur du flux
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore le reste de la ligne invalide
    }

    // Utilisation d'un bloc try-catch pour la création de la matrice au cas où les dimensions seraient 0 ou négatives (bien que déjà géré par les boucles)
    Matrice<T> mat(lignes, colonnes);
    std::cout << "Entrez les elements de la matrice " << nom << " (" << lignes << "x" << colonnes << ") :" << std::endl;
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            T value;
            std::cout << "Element[" << i << "][" << j << "] : ";
            // Boucle de validation pour chaque élément
            while (!(std::cin >> value)) {
                std::cout << "Saisie invalide. Entrez une valeur numerique pour l'element[" << i << "][" << j << "] : ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            mat.setElement(i, j, value);
        }
    }
    return mat;
}

int main() {
    // Utilisation de try-catch pour gérer les exceptions (dimensions, hors limites, incompatibilité d'opération)
    try {
        // Demander à l'utilisateur de saisir les deux matrices (type int)
        Matrice<int> mat1 = demanderMatrice<int>("A (entiers)");
        std::cout << "\nMatrice A :" << std::endl;
        std::cout << mat1 << std::endl; // Affichage via l'opérateur <<

        Matrice<int> mat2 = demanderMatrice<int>("B (entiers)");
        std::cout << "\nMatrice B :" << std::endl;
        std::cout << mat2 << std::endl; // Affichage via l'opérateur <<

        // Addition des matrices
        std::cout << "Tentative d'addition de A et B..." << std::endl;
        Matrice<int> matSomme = mat1 + mat2; // Addition via l'opérateur +
        std::cout << "\nResultat de l'addition (A + B) :" << std::endl;
        std::cout << matSomme << std::endl; // Affichage via l'opérateur <<

        // --- Test avec des matrices de type double (extension facultative) ---
        // Décommenter le bloc ci-dessous pour tester avec des nombres décimaux
        /*
        std::cout << "\n--- Test avec des matrices de doubles ---" << std::endl;
        Matrice<double> matD1 = demanderMatrice<double>("C (doubles)");
        std::cout << "\nMatrice C :" << std::endl;
        std::cout << matD1 << std::endl;

        Matrice<double> matD2 = demanderMatrice<double>("D (doubles)");
        std::cout << "\nMatrice D :" << std::endl;
        std::cout << matD2 << std::endl;

        Matrice<double> matDSomme = matD1 + matD2;
        std::cout << "\nResultat de l'addition (C + D) :" << std::endl;
        std::cout << matDSomme << std::endl;
        */

        // Exemple pour tester une erreur de dimension lors de l'addition (décommenter pour voir l'exception)
        /*
        std::cout << "\n--- Test d'erreur : Addition de matrices de dimensions differentes ---" << std::endl;
        Matrice<int> matErreur1(2, 2);
        matErreur1.setElement(0,0,1); matErreur1.setElement(0,1,2);
        matErreur1.setElement(1,0,3); matErreur1.setElement(1,1,4);

        Matrice<int> matErreur2(2, 3); // Dimensions differentes
        matErreur2.setElement(0,0,5); matErreur2.setElement(0,1,6); matErreur2.setElement(0,2,7);
        matErreur2.setElement(1,0,8); matErreur2.setElement(1,1,9); matErreur2.setElement(1,2,0);

        std::cout << "Matrice Erreur 1 (2x2) :\n" << matErreur1 << std::endl;
        std::cout << "Matrice Erreur 2 (2x3) :\n" << matErreur2 << std::endl;

        Matrice<int> matSommeErreur = matErreur1 + matErreur2; // Ceci déclenchera l'exception
        std::cout << "Cette ligne ne devrait pas s'afficher si l'exception est levée." << std::endl;
        */

    } catch (const std::invalid_argument& e) {
        // Attrapée si le constructeur Matrice est appelé avec des dimensions <= 0
        std::cerr << "\nErreur de construction de matrice : " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        // Attrapée si getElement ou setElement est appelé avec des indices hors limites
        std::cerr << "\nErreur d'accès aux éléments : " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        // Attrapée si l'opérateur + est appelé avec des matrices de dimensions incompatibles
        std::cerr << "\nErreur d'opération sur les matrices : " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // Attrape toute autre exception standard
        std::cerr << "\nUne erreur inattendue est survenue : " << e.what() << std::endl;
    } catch (...) {
        // Attrape toute autre exception non standard
        std::cerr << "\nUne erreur inconnue est survenue." << std::endl;
    }

    return 0;
}