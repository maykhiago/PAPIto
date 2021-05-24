#ifndef _PAPITO_H
#define _PAPITO_H

#include <stdlib.h>
#include <stdio.h>
#include <papi.h>
#include <omp.h>

// Internal functions
void papito_input();
void papito_handle_error (int retval);

// User functions
void papito_init();
void papito_start();
void papito_end();

#endif
