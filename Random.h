/* ========================================================================
 * RANDOM.H
 * ========================================================================

 * ------------------------------------------------------------------------
 * DEFINICOES        - funcoes de randomizacao de numero
 * -------------------------------------------------------------------------- */

#ifndef _RANDOM_H_
#define _RANDOM_H_ 1

#include <stdlib.h>
#include <math.h>
#include <time.h>

// -----------------------------------------------------------------------
// - Inicializa uma seed para gerar numeros aleatorios
// -----------------------------------------------------------------------
inline int randomize() {
    int t = time(NULL);
    srand(t);
    return t;
}

inline void randomize(unsigned int seed) {
    srand(seed);
}

void fun(char aef, char in);

// -----------------------------------------------------------------------
// - Retorna um numero aleatorio
// -----------------------------------------------------------------------
inline double rnd(float max) {
    return max * rand() / (RAND_MAX + 1.0);
}

#endif
