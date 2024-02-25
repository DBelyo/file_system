#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit.h"
#include "debug.h"

void procedure_fin() {
	fermer_sortie_debug();
	fermer_entree_instruction();
}

void exit_malloc() {
	puts("Échec de malloc: impossible d'allouer de la mémoire");
	fermer_sortie_debug();
	exit(MALLOC);
}

void exit_pas_de_nom() {
	puts("Il faut préciser le nom de la destination");
	procedure_fin();
	exit(PAS_DE_NOM);
}

void exit_nombre_d_argument(char *cmd, int attendus, int actuels) {
  if (strcmp(cmd,"cd") == 0)
		printf("\"%s\" attend au plus 1 argument. %d donné(s)\n", cmd, actuels);
  else
	printf("\"%s\" attend %d arguments. %d donné(s)\n", cmd, attendus, actuels);

  procedure_fin();
  exit(NB_ARGUMENT);
}

void exit_noeud_null(char *nom) {
	printf("Aucun fichier ou dossier de ce type : \"%s\"\n", nom);
	procedure_fin();
	exit(NOEUD_INEXISTANT);
}

void exit_noeud_existant(char *nom) {
	printf ("Impossile de creer le dossier/fichier \"%s\": Le fichier existe déjà\n", nom);
	procedure_fin();
	exit(NOEUD_DEJA_EXISTANT);
}

void exit_nom_invalide(char *nom) {
	puts("Nom invalide: un nom de fichier / dossier doit faire moins de 100 caractères, uniquement alphanumériques");
	printf("nom donné: %s\n", nom);
	procedure_fin();
	exit(NOM_INVALIDE);
}

void exit_commande_invalide(char *nom) {
	printf("Commande invalide : %s\n", nom);
	procedure_fin();
	exit(COMMANDE_INVALIDE);
}

void exit_pas_un_dossier(char *nom) {
	printf("%s n'est pas un dossier\n", nom);
	procedure_fin();
	exit(PAS_UN_DOSSIER);
}

void exit_suppression_impossible(char *src, char *dst) {
	puts("Impossible de supprimer un dossier parent");
	printf("%s est un parent de %s\n", dst, src);
	procedure_fin();
	exit(SUPPRESSION_IMPOSSIBLE);
}

void exit_copie_impossible(char *src, char *dst) {
	puts("Impossible de copier un dossier parent dans un de ses dossier fils ou l'élément copié est déjà dans le dossier ciblé");
	printf("%s est un parent de %s\n", dst, src);
	procedure_fin();
	exit(COPIE_IMPOSSIBLE);
}

void exit_deplacement_impossible(char *src, char *dst) {
	puts("Impossible de déplcer un dossier parent dans un de ses dossier fils ou l'élément déplacé est déja dans le dossier ciblé");
	printf("%s est un parent de %s\n", dst, src);
	procedure_fin();
	exit(DEPLACEMENT_IMPOSSIBLE);
}

void exit_trop_d_arguments(char *cmd) {
	printf("La commande %s attend moins d'arguments", cmd);
	procedure_fin();
	exit(NB_ARGUMENT);
}

void exit_chemin_mal_forme(char *s) {
	printf("Le chemin %s est mal formé\n", s);
	puts("un chemin ne peut pas terminer par un /, en dehors du chemin \"/\"");
	procedure_fin();
	exit(CHEMIN_MAL_FORME);
}
