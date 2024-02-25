#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"

static FILE *SORTIE_DEBUG;
static FILE *ENTREE_INSTRUCTION;

void flog(const char *message) {
	if (SORTIE_DEBUG == NULL) return;
	fputs(message, SORTIE_DEBUG);
	fputs("\n", SORTIE_DEBUG);
}

void flogf(const char *message, ...) {
	if (SORTIE_DEBUG == NULL) return;
	va_list args;

	va_start(args, message);
	vfprintf(SORTIE_DEBUG, message, args);
	va_end(args);
}

void set_sortie_debug(FILE *sortie) {
	fermer_sortie_debug();
	SORTIE_DEBUG = sortie;
}

void fermer_sortie_debug() {
	if (SORTIE_DEBUG != NULL)
		fclose(SORTIE_DEBUG);
}

void set_entree_instruction(FILE *entree) {
	fermer_entree_instruction();
	ENTREE_INSTRUCTION = entree;
}

void fermer_entree_instruction() {
	if (ENTREE_INSTRUCTION != NULL)
		fclose(ENTREE_INSTRUCTION);
}
