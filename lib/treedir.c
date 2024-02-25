#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "debug.h"
#include "arbre.h"
#include "liste.h"
#include "instruction.h"
#include "exit.h"

bool obtenir_ligne(char **ligne, size_t *MAX_LENGTH, FILE *fichier) {
	fgets(*ligne, *MAX_LENGTH, fichier);
	if (feof(fichier)) return true;

	char *tampon = NULL;

	while (strlen(*ligne) + 1 == *MAX_LENGTH) {
		*MAX_LENGTH += 256;
		*ligne = realloc(*ligne, *MAX_LENGTH);
		tampon = malloc(257 * sizeof(char));
		if (*ligne == NULL || tampon == NULL) exit_malloc();
		fgets(tampon, 257, fichier);
		strcat(*ligne, tampon);
	}

	free(tampon);
	// on retire le saut de ligne
	char *last = *ligne + strlen(*ligne)-1;
	if (*last == '\n') *last = '\0';

	// on saute les lignes vides
	if (**ligne == '\0') return obtenir_ligne(ligne, MAX_LENGTH, fichier);
	return false;
}

int main(int argc, char *argv[]) {
	if (argc == 3 && strcmp("--debug", argv[2]) == 0) {
		FILE *sortie = fopen("log", "w");
		set_sortie_debug(sortie);
	} else if (argc != 2) {
		puts("Le programme attend exactement un fichier d'instruction en argument.");
		printf("(%d donné(s)).\n", argc);
		exit(1);
	}

	flog("ouverture du fichier instruction");
	FILE *fichier_instructions = fopen(argv[1], "r");

	if (fichier_instructions == NULL) {
		puts("Impossible de lire le fichier passé en argument.");
		exit(1);
	}
	set_entree_instruction(fichier_instructions);
	noeud* arbre = creer_arbre();

	size_t t = 256;
	char *ligne = malloc(t * sizeof(char));
	instruction *instr = NULL;
	int numero_ligne = 0;

	while (!obtenir_ligne(&ligne, &t, fichier_instructions)) {
		++numero_ligne;
		flogf("\nlecture de l'instruction ligne %d:\n%s\n", numero_ligne, ligne);
		afficher_prompt(arbre);
		printf("%s\n", ligne);
		instr = generer_instruction(ligne);
		arbre = traiter_instruction(arbre, instr);
		free(instr);
	}

	flogf("\nfin de lecture des instructions\nlibération de la mémoire\n");
	free(ligne);
	liberer_noeud(arbre->racine);
	fermer_sortie_debug();
	fclose(fichier_instructions);

	return EXIT_SUCCESS;
}
