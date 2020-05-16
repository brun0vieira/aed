/***********************************************************
 * TAD Trampolim
 * .h
 **********************************************************/

#ifndef _H_TRAMPOLIM
#define _H_TRAMPOLIM

#include "visitante.h"

typedef struct _trampolim * trampolim;

trampolim criaTrampolim();

void destroiTrampolim(trampolim t);

int disponibilidadeTrampolim(trampolim t);

void colocaNoTrampolim(trampolim t, visitante v, int h_entrada, int m_entrada);

visitante visitanteTrampolim(trampolim t);

int tempoEntradaTrampolim(trampolim t);

visitante saidaTrampolim(trampolim t);

#endif // _H_TRAMPOLIM
