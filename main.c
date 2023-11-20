#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure pour une proposition
typedef struct proposition {
    char id;
    bool valeur;
    struct proposition* suiv;
} proposition;

// Structure pour une règle
typedef struct regle {
    proposition* premisse;
    proposition* conclusion;
    struct regle* suiv;
} regle;

// Structure pour la base de connaissances
typedef struct {
    regle* regles;
} BC;

// Fonction pour créer une nouvelle proposition
proposition* creerProposition(char id, bool valeur) {
    proposition* nouvelleProposition = (proposition*)malloc(sizeof(proposition));
    if (nouvelleProposition != NULL) {
        nouvelleProposition->id = id;
        nouvelleProposition->valeur = valeur;
        nouvelleProposition->suiv = NULL;
    }
    return nouvelleProposition;
}

// Fonction pour créer une nouvelle règle
regle* creerRegle(proposition* premisse, proposition* conclusion) {
    regle* nouvelleRegle = (regle*)malloc(sizeof(regle));
    if (nouvelleRegle != NULL) {
        nouvelleRegle->premisse = premisse;
        nouvelleRegle->conclusion = conclusion;
        nouvelleRegle->suiv = NULL;
    }
    return nouvelleRegle;
}

// Fonction pour créer une nouvelle base de connaissances
BC creerBC(regle* regles) {
    BC nouvelleBC;
    nouvelleBC.regles = regles;
    return nouvelleBC;
}

// Fonction pour ajouter une proposition à une liste de propositions
proposition* ajouterPropositionAListe(proposition* liste, char id, bool valeur) {
    proposition* nouvelleProposition = creerProposition(id, valeur);
    if (nouvelleProposition != NULL) {
        nouvelleProposition->suiv = liste;
        return nouvelleProposition;
    } else {
        return liste; // Retourner la liste inchangée en cas d'erreur
    }
}

// Fonction pour afficher une proposition
void afficherProposition(proposition* prop) {
    if (prop != NULL) {
        printf("%c %s", prop->id, prop->valeur ? "Vrai" : "Faux");
        if (prop->suiv != NULL) {
            printf(" ET ");
            afficherProposition(prop->suiv);
        } else {
            printf("\n");
        }
    }
}

// Fonction pour afficher une règle
void afficherRegle(regle* r) {
    if (r != NULL) {
        printf("Regle :\n");
        printf("  Premisse : ");
        afficherProposition(r->premisse);
        printf("  Conclusion : ");
        afficherProposition(r->conclusion);
        printf("\n");
        afficherRegle(r->suiv);
    }
}

// Fonction pour libérer la mémoire d'une liste de propositions
void libererListePropositions(proposition* prop) {
    while (prop != NULL) {
        proposition* suivant = prop->suiv;
        free(prop);
        prop = suivant;
    }
}

// Fonction pour libérer la mémoire d'une règle
void libererRegle(regle* r) {
    if (r != NULL) {
        libererListePropositions(r->premisse);
        libererListePropositions(r->conclusion);
        free(r);
    }
}

// Fonction pour libérer la mémoire de la base de connaissances
void libererBC(BC baseConnaissances) {
    libererRegle(baseConnaissances.regles);
}

int main() {
    // Création de quelques propositions
    proposition* propositionA = creerProposition('A', true);
    proposition* propositionB = creerProposition('B', false);
    proposition* propositionC1 = creerProposition('C', true);
    proposition* propositionC2 = creerProposition('C', false);

    // Création d'une règle initiale
    regle* regle1 = creerRegle(propositionA, propositionB);
    printf("Regle avant ajout a la premisse :\n");
    afficherRegle(regle1);

    // Ajout de propositions à la prémisse
    regle1->premisse = ajouterPropositionAListe(regle1->premisse, 'C', true);

    // Affichage de la règle mise à jour
    printf("Regle apres ajout a la premisse :\n");
    afficherRegle(regle1);

    // Ajout d'une proposition à la conclusion
    regle1->conclusion = ajouterPropositionAListe(regle1->conclusion, 'D', false);

    // Affichage de la règle mise à jour
    printf("Regle apres ajout a la conclusion :\n");
    afficherRegle(regle1);

    // Ajout d'une condition à la règle
    regle1->premisse = ajouterPropositionAListe(regle1->premisse, 'C', false);

    // Affichage de la règle mise à jour
    printf("Regle apres ajout d'une condition a la regle :\n");
    afficherRegle(regle1);

    // Libération de la mémoire
    libererRegle(regle1);
    libererListePropositions(propositionA);
    libererListePropositions(propositionB);
    libererListePropositions(propositionC1);
    libererListePropositions(propositionC2);

    return 0;
}
