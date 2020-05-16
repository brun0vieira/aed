/***********************************************************
 * TAD Trampolim
 * .c
 **********************************************************/

 #include <stdio.h>
 #include <stdlib.h>

 #include "trampolim.h"
 #include "visitante.h"

 struct _trampolim {

     int h_entrada, m_entrada, disponibilidade;
     visitante v;

 };

 trampolim criaTrampolim() {

    trampolim t = (trampolim)malloc(sizeof(struct _trampolim));

    if(t==NULL)
        return NULL;

    t->disponibilidade = 1;

    return t;

 }

 void destroiTrampolim(trampolim t) {

    free(t);

 }

 int disponibilidadeTrampolim(trampolim t) {

    return t->disponibilidade;

 }

 void colocaNoTrampolim(trampolim t, visitante v, int h_entrada, int m_entrada) {

    t->disponibilidade=0;
    t->h_entrada=h_entrada;
    t->m_entrada=m_entrada;
    t->v=v;

 }

 visitante visitanteTrampolim(trampolim t) {

    return t->v;

 }

 int tempoEntradaTrampolim(trampolim t) {

    return (t->h_entrada * 60) + t->m_entrada;

 }

 visitante saidaTrampolim(trampolim t) {

    t->disponibilidade=1;
    return t->v;

 }
