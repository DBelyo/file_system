#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "arbre.h"
#include "liste.h"
#include "exit.h"
#include "debug.h"

liste_noeud *creer_liste() {
	flog("création d'une liste");

    liste_noeud *l = malloc(sizeof(liste_noeud));

    if (l == NULL) exit_malloc();

	l->no = NULL;
	l->succ = NULL;

    return l;
}

liste_noeud *creer_liste_avec_noeud(noeud *n) {
    if (n == NULL) return creer_liste();

	flogf("création d'une liste à partir du noeud %s\n", n->nom);
    liste_noeud *l = malloc(sizeof(liste_noeud));

	if (l == NULL) exit_malloc();

    l->no = n;
    l->succ = NULL;

    return l;
}

void copier_liste(noeud *pere, liste_noeud *l) {
	if (l == NULL) return;

	copier_noeud(pere, l->no, l->no->nom);
	copier_liste(pere, l->succ);
}

void liberer_liste(liste_noeud *l) {
	if (l == NULL) return;

	liberer_noeud(l->no);
	liberer_liste(l->succ);
	free(l);
}

noeud *get_elt(liste_noeud *l, char *nom) {
	assert(l != NULL);

	if (l->no == NULL) return NULL;
    if(strcmp(nom,l->no->nom) == 0) return l->no;
    if(l->succ == NULL) return NULL;
    return get_elt(l->succ, nom);
}

void ajouter_elt(liste_noeud *l, noeud *n) {
	assert(l != NULL);
	assert(n != NULL);

	if (l->no == NULL) {
		l->no = n;
		return;
	}

	while(l->succ != NULL) {
		if (strcmp(l->no->nom, n->nom) == 0) {
			exit_noeud_existant(n->nom);
		}
		l = l->succ;
	}
	if (strcmp(l->no->nom, n->nom) == 0) {
		exit_noeud_existant(n->nom);
	}
	l->succ = creer_liste_avec_noeud(n);
}

void affiche_liste(liste_noeud *l) {
    if(l == NULL || l->no == NULL){
		puts("");
		return;
	}

	if (l->no->est_dossier) printf("%s (D)", l->no->nom);
	else printf("%s (F)", l->no->nom);

	if (l->succ != NULL) printf(", ");
	affiche_liste(l->succ);
}

void print_liste(liste_noeud *l) {
	assert(l != NULL);

	if (l->no == NULL) return;
	print_noeud(l->no);

	if (l->succ != NULL) print_liste(l->succ);
}

size_t taille_liste(liste_noeud *l){
	if (l == NULL || l->no == NULL) return 0;
	return 1 + taille_liste(l->succ);
}

void supprimer_elt(liste_noeud* l, noeud* n) {
	assert(n != NULL);
	flogf("suppression du noeud %s de la liste\n", n->nom);

	if (l == NULL || l->no == NULL) {
		exit_noeud_null(l->no->nom);
	}

    if  (n == l->no) {
		if (l->succ == NULL) {
			l->no = NULL;
		} else {
			liste_noeud *a_suppr = l->succ;
			l->no = l->succ->no;
			l->succ = l->succ->succ;
			free(a_suppr);
		}
		return;
    }

	while(l->succ != NULL) {
		if (l->succ->no == n) {
			liste_noeud *a_suppr = l->succ;
			l->succ = l->succ->succ;
			free(a_suppr);
			return;
		}
		l = l->succ;
	}
	exit_noeud_null(n->nom);
}
