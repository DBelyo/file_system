#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arbre.h"
#include "liste.h"
#include "exit.h"
#include "debug.h"

struct chemin {
	bool est_absolu;
	size_t profondeur;
	size_t curseur;
	char **noeuds;
};

static char **decoupe_chemin(char*, bool*, size_t*);

char *dupliquer_chaine(char *s) {
	assert(s != NULL);

	char *copie = malloc((strlen(s) + 1) * sizeof(char));
	strcpy(copie, s);
	return copie;
}

chemin *generer_chemin(char *noeuds) {
    chemin *chem = malloc(sizeof(chemin));
    if (chem == NULL) exit_malloc();

    chem->noeuds = decoupe_chemin(noeuds, &chem->est_absolu, &chem->profondeur);
	chem->curseur = 0;
    return chem;
}

void liberer_chemin(chemin *chem) {
	assert(chem != NULL);

	free(chem->noeuds);
	free(chem);
}

noeud *creer_arbre() {
	flog("initialisation de l'arbre");
	noeud* racine = malloc(sizeof(noeud));

	if (racine == NULL) exit_malloc();

	racine->est_dossier = true;
	racine->racine = racine;
	racine->fils = creer_liste();
	racine->pere = racine;
	racine->nom = dupliquer_chaine("");

	return racine;
}

noeud *creer_fichier(noeud *pere, char *nom) {
	assert(pere != NULL);
	if(!est_nom_valide(nom)) exit_nom_invalide(nom);

	flogf("création du fichier %s dans %s\n", nom, pere->nom);

	noeud *fichier = malloc(sizeof(noeud));

	if (fichier == NULL) exit_malloc();

	fichier->est_dossier = false;
	fichier->racine = pere->racine;
	fichier->pere = pere;
	fichier->nom = dupliquer_chaine(nom);
	ajouter_elt(pere->fils, fichier);

	return fichier;
}


noeud *creer_dossier(noeud *pere, char *nom, liste_noeud *fils) {
	assert(pere != NULL);
	if(!est_nom_valide(nom)) exit_nom_invalide(nom);

	flogf("création du dossier %s dans %s\n", nom, pere->nom);

	noeud *dossier = malloc(sizeof(noeud));

	if (dossier == NULL) exit_malloc();

	dossier->est_dossier = true;
	dossier->racine = pere->racine;
	dossier->fils = fils;
	dossier->pere = pere;
	dossier->nom = dupliquer_chaine(nom);
	ajouter_elt(pere->fils, dossier);

	return dossier;
}

noeud *copier_noeud(noeud* pere, noeud *n, char *nom) {
	assert(pere != NULL);
	if (n == NULL) return NULL;

	flogf("copie de %s en %s dans %s\n", n->nom, nom, pere->nom);
	if(n->est_dossier) {
		noeud *copie = creer_dossier(pere, nom, creer_liste());
		copier_liste(copie, n->fils);
		return copie;
	}

	return creer_fichier(pere, n->nom);
}

void afficher_chemin(noeud *n) {
	assert(n != NULL);

	if (n->pere != n->racine) afficher_chemin(n->pere);
	printf("/%s", n->nom);
}

void liberer_noeud(noeud *n) {
	if (n == NULL) return;
	flogf("libération de %s\n", n->nom);

	if (n->est_dossier) liberer_liste(n->fils);

	free(n->nom);
	free(n);
}

void ajouter_noeud(noeud *pere, noeud *n) {
	assert(pere != NULL);
	assert(n != NULL);

	flogf("ajout de %s dans %s\n", n->nom, pere->nom);
	ajouter_elt(pere->fils, n);
}

static char **decoupe_chemin(char *chemin, bool *est_absolu, size_t *taille) {
    assert(chemin != NULL);
    assert(*chemin != '\0');

    if (*chemin == '/') {
        *est_absolu = true;
        chemin = chemin + 1;
		if (*chemin == '\0') {
			// chemin vers la racine
			*taille = 0;
			return NULL;
		}
    } else {
        *est_absolu = false;
    }

    size_t len = strlen(chemin);
	if (*(chemin + len - 1) == '/')  exit_chemin_mal_forme(chemin);

    size_t nb_noeuds = 1;

    for (size_t i = 0; i < len; ++i)
        if (*(chemin + i) == '/') ++nb_noeuds;

    *taille = nb_noeuds;

    char **chemin_decoupe = malloc(nb_noeuds * sizeof(char*));
    *chemin_decoupe = strtok(chemin, "/");

    for (size_t i = 1; i < nb_noeuds; ++i)
        *(chemin_decoupe + i) = strtok(NULL, "/");

    return chemin_decoupe;
}

char *sans_dernier_noeud(chemin *chem) {
	assert(chem != NULL && chem->profondeur > 0);

	return chem->noeuds[--chem->profondeur];
}

noeud *aller_a(noeud *n, chemin *chem) {
	assert(chem != NULL);
    assert(n != NULL);

    if (chem->est_absolu) {
        chem->est_absolu = false;
        flog("déplacement à la racine");
        return aller_a(n->racine, chem);
    }

    if (chem->curseur == chem->profondeur) return n;

    char *nom = *(chem->noeuds + chem->curseur);
    ++chem->curseur;

    if ((strcmp(nom, "..") == 0) && n->pere != NULL) {
	   flogf("déplacement vers le pere de %s (%s)\n", nom, n->pere->nom);
       return aller_a(n->pere, chem);
	}

	if (strcmp(nom, ".") == 0) return aller_a(n,chem);

    noeud *suivant = get_elt(n->fils, nom);

    if (suivant == NULL) exit_noeud_null(nom);

    if (!suivant->est_dossier) {
		if (chem->curseur == chem->profondeur) return suivant;
		else exit_pas_un_dossier(suivant->nom);
	}

    flogf("déplacement vers %s\n", nom);
    return aller_a(suivant, chem);
}

bool est_parent(noeud *src, noeud *dst) {
   if (dst == src) return true;
   if (dst == dst->racine) return false;
   return est_parent(src, dst->pere);
}

void print_noeud(noeud *n) {
	assert(n != NULL);
	flogf("affichage du noeud %s\n", n->nom);

	if (!n->est_dossier) {
		printf("Noeud %s (F), pere : %s, 0 fils\n", n->nom, n->pere->nom);
		return;
	}

	size_t taille = taille_liste(n->fils);

	if (n == n->racine) printf("Noeud / (D)");
	else printf("Noeud %s (D), pere : %s", n->nom, n->pere->nom);

	printf(", %lu fils : ", taille);
	affiche_liste(n->fils);

	if (taille > 0) print_liste(n->fils);
}

bool est_nom_valide(char *input) {
	size_t taille = strlen(input);

	if (taille > 100 || taille <= 0) exit_nom_invalide(input);

	for (size_t t = 0; t < taille; ++t) {
		if (!isalnum(input[t])) {
			return false;
		}
	}
	return true;
}
