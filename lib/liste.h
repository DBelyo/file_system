#ifndef LISTE_H
#define LISTE_H

#include "arbre.h"

struct liste_noeud;

struct liste_noeud {
	struct noeud *no;
	struct liste_noeud *succ;
};

typedef struct liste_noeud liste_noeud;
typedef struct noeud noeud;

extern liste_noeud *creer_liste();
extern liste_noeud *creer_liste_avec_noeud(noeud*);
extern void copier_liste(noeud*, liste_noeud*);
extern void liberer_liste(liste_noeud*);

extern size_t taille_liste(liste_noeud*);
extern noeud *get_elt(liste_noeud*, char*);
extern void ajouter_elt (liste_noeud*, noeud*);
extern void supprimer_elt(liste_noeud*, noeud*);
extern void affiche_liste(liste_noeud*);
extern void print_liste(liste_noeud*);
#endif
