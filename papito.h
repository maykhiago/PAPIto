#ifndef _PAPITO_H			 /* _ENERGY_ARM_H */
#define _PAPITO_H

#include <stdlib.h>
#include <stdio.h>
#include <papi.h>
#include <omp.h>

#define INDEX_CYCLE 0
#define INDEX_INST 1
#define INDEX_L1I  2
#define INDEX_L1D  3

void papito_handle_error (int retval);

void papito_init();

// Para quando medido tudo, do inicio ao fim sem separar por regiao paralela e não tem adaptação do numero de threads
void papito_start();
void papito_end();

#endif /* _PAPITO_H */
