#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>

#include "arbre.h"
#include "debug.h"

typedef struct instruction instruction;

extern void afficher_prompt(noeud*);
extern instruction *generer_instruction(char*);
extern noeud *traiter_instruction(noeud*, instruction*);

#endif
