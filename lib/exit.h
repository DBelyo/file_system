#ifndef ERREUR_H
#define ERREUR_H

#include <stdio.h>


enum exit {OK, MALLOC,
	PAS_DE_NOM, NB_ARGUMENT,
	NOEUD_INEXISTANT, NOEUD_DEJA_EXISTANT,
	NOM_INVALIDE, COMMANDE_INVALIDE,
	PAS_UN_DOSSIER, SUPPRESSION_IMPOSSIBLE,
	COPIE_IMPOSSIBLE, DEPLACEMENT_IMPOSSIBLE,
	CHEMIN_MAL_FORME};

extern void exit_malloc(void);
extern void exit_pas_de_nom(void);
extern void exit_nombre_d_argument(char*, int, int);
extern void exit_noeud_null(char*);
extern void exit_noeud_existant(char*);
extern void exit_nom_invalide(char*);
extern void exit_commande_invalide(char*);
extern void exit_pas_un_dossier(char*);
extern void exit_suppression_impossible(char*, char*);
extern void exit_copie_impossible(char*, char*);
extern void exit_deplacement_impossible(char*, char*);
extern void exit_trop_d_arguments(char*);
extern void exit_chemin_mal_forme(char*);

#endif
