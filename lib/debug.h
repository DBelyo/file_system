#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

extern void flog(const char*);
extern void flogf(const char*, ...);
extern void set_sortie_debug(FILE*);
extern void fermer_sortie_debug(void);
extern void set_entree_instruction(FILE*);
extern void fermer_entree_instruction(void);

#endif
