#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes ---
#define MAX_LIGNES 1000      // Max lignes dans le fichier
#define MAX_TAILLE 1024      // Max taille d'une ligne

// --- Prototypes des fonctions ---
void afficher_menu();
void afficher_contenu(char **lignes, int nb_lignes);
void ajouter_ligne(char **lignes, int *nb_lignes);
void inserer_ligne(char **lignes, int *nb_lignes);
void supprimer_ligne(char **lignes, int *nb_lignes);
void modifier_ligne(char **lignes, int nb_lignes);
void sauvegarder(char **lignes, int nb_lignes, const char *nom_fichier);
void liberer_lignes(char **lignes, int nb_lignes);

// --- main() ---
int main() {
    char *lignes[MAX_LIGNES]; // Tableau de chaînes dynamiques
    int nb_lignes = 0;
    char nom_fichier[100];
    FILE *fichier;
    char buffer[MAX_TAILLE];

    // Initialisation du tableau à NULL
    for (int i = 0; i < MAX_LIGNES; i++) {
        lignes[i] = NULL;
    }

    // Demander le nom du fichier
    printf("Nom du fichier à éditer : ");
    fgets(nom_fichier, sizeof(nom_fichier), stdin);
    nom_fichier[strcspn(nom_fichier, "\n")] = '\0'; // enlever le \n

    // Ouvrir le fichier et lire son contenu
    fichier = fopen(nom_fichier, "r");
    if (fichier != NULL) {
        while (fgets(buffer, MAX_TAILLE, fichier) && nb_lignes < MAX_LIGNES) {
            lignes[nb_lignes] = malloc(strlen(buffer) + 1);
            strcpy(lignes[nb_lignes], buffer);
            nb_lignes++;
        }
        fclose(fichier);
    }

    // --- Boucle principale ---
    int choix;
    do {
        afficher_menu();
        scanf("%d", &choix);
        getchar(); // consommer le \n

        switch (choix) {
            case 1: afficher_contenu(lignes, nb_lignes); break;
            case 2: ajouter_ligne(lignes, &nb_lignes); break;
            case 3: inserer_ligne(lignes, &nb_lignes); break;
            case 4: supprimer_ligne(lignes, &nb_lignes); break;
            case 5: modifier_ligne(lignes, nb_lignes); break;
            case 6: sauvegarder(lignes, nb_lignes, nom_fichier); break;
            case 7: printf("Fermeture de l'éditeur...\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 7);

    // Libération mémoire
    liberer_lignes(lignes, nb_lignes);
    return 0;
}

// --- Fonctions ---

void afficher_menu() {
    printf("\n--- MENU ---\n");
    printf("1. Afficher le contenu\n");
    printf("2. Ajouter une ligne à la fin\n");
    printf("3. Insérer une ligne à une position\n");
    printf("4. Supprimer une ligne\n");
    printf("5. Modifier une ligne\n");
    printf("6. Sauvegarder\n");
    printf("7. Quitter\n");
    printf("-------------\n");
    printf("Votre choix : ");

}

void afficher_contenu(char **lignes, int nb_lignes) {
    printf("\n--- CONTENU DU FICHIER ---\n");
    for (int i = 0; i < nb_lignes; i++) {
        printf("%d: %s", i + 1, lignes[i]);
    }
}

void ajouter_ligne(char **lignes, int *nb_lignes) {
    if (*nb_lignes >= MAX_LIGNES) {
        printf("Nombre maximum de lignes atteint.\n");
        return;
    }
    char buffer[MAX_TAILLE];
    printf("Entrez la ligne à ajouter : ");
    fgets(buffer, MAX_TAILLE, stdin);
    lignes[*nb_lignes] = malloc(strlen(buffer) + 1);
    strcpy(lignes[*nb_lignes], buffer);
    (*nb_lignes)++;
}

void inserer_ligne(char **lignes, int *nb_lignes) {
    int pos;
    char buffer[MAX_TAILLE];

    if (*nb_lignes >= MAX_LIGNES) return;

    printf("À quelle position (1 à %d) ? ", *nb_lignes + 1);
    scanf("%d", &pos); getchar();

    if (pos < 1 || pos > *nb_lignes + 1) {
        printf("Position invalide.\n");
        return;
    }

    printf("Entrez la ligne à insérer : ");
    fgets(buffer, MAX_TAILLE, stdin);

    for (int i = *nb_lignes; i >= pos; i--) {
        lignes[i] = lignes[i - 1];
    }

    lignes[pos - 1] = malloc(strlen(buffer) + 1);
    strcpy(lignes[pos - 1], buffer);
    (*nb_lignes)++;
}

void supprimer_ligne(char **lignes, int *nb_lignes) {
    int pos;
    printf("Ligne à supprimer (1 à %d) : ", *nb_lignes);
    scanf("%d", &pos); getchar();

    if (pos < 1 || pos > *nb_lignes) {
        printf("Position invalide.\n");
        return;
    }

    free(lignes[pos - 1]);
    for (int i = pos - 1; i < *nb_lignes - 1; i++) {
        lignes[i] = lignes[i + 1];
    }

    (*nb_lignes)--;
}

void modifier_ligne(char **lignes, int nb_lignes) {
    int pos;
    char buffer[MAX_TAILLE];

    printf("Ligne à modifier (1 à %d) : ", nb_lignes);
    scanf("%d", &pos); getchar();

    if (pos < 1 || pos > nb_lignes) {
        printf("Position invalide.\n");
        return;
    }

    printf("Nouvelle ligne : ");
    fgets(buffer, MAX_TAILLE, stdin);

    free(lignes[pos - 1]);
    lignes[pos - 1] = malloc(strlen(buffer) + 1);
    strcpy(lignes[pos - 1], buffer);
}

void sauvegarder(char **lignes, int nb_lignes, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de la sauvegarde.\n");
        return;
    }

    for (int i = 0; i < nb_lignes; i++) {
        fprintf(fichier, "%s", lignes[i]);
    }

    fclose(fichier);
    printf("Fichier sauvegardé avec succès.\n");
}

void liberer_lignes(char **lignes, int nb_lignes) {
    for (int i = 0; i < nb_lignes; i++) {
        free(lignes[i]);
    }
}

