#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

// Fonction pour nettoyer un mot : suppression ponctuation + passage en minuscule
std::string nettoyerMot(const std::string& mot) {
    std::string nettoye;
    for (char c : mot) {
        if (std::isalpha(c) || std::isdigit(c)) {
            nettoye += std::tolower(c);
        }
    }
    return nettoye;
}

int main() {
    std::string nomFichier;
    std::cout << "Entrez le nom du fichier texte a analyser : ";
    std::getline(std::cin, nomFichier);

    std::ifstream fichier(nomFichier);
    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier \"" << nomFichier << "\"." << std::endl;
        return 1;
    }

    std::map<std::string, int> frequenceMots;
    std::string mot;

    while (fichier >> mot) {
        std::string motNettoye = nettoyerMot(mot);
        if (!motNettoye.empty()) {
            frequenceMots[motNettoye]++;
        }
    }

    fichier.close();

    // Transférer vers un vecteur pour trier par fréquence
    std::vector<std::pair<std::string, int>> motsFrequences(frequenceMots.begin(), frequenceMots.end());

    // Trier par fréquence décroissante
    std::sort(motsFrequences.begin(), motsFrequences.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    // Afficher les 10 mots les plus fréquents
    std::cout << "\nLes 10 mots les plus frequents sont :\n";
    int compteur = 0;
    for (const auto& [mot, freq] : motsFrequences) {
        std::cout << mot << " : " << freq << std::endl;
        if (++compteur >= 10) break;
    }

    return 0;
}
