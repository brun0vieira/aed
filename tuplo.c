#include <stdlib.h>
#include <string.h>

#include "tuplo.h"

/* Tipo do TAD tuplo */
struct _tuplo {
	void * priElem;
	void * segElem;
};

/* Prot�tipos das fun��es associadas a um tuplo - TAD tuplo */
tuplo criaTuplo(int tipoPri, void * pri, void * seg){
	tuplo aux = (tuplo) malloc(sizeof(struct _tuplo));
		if (aux == NULL)
			return NULL;
		if (tipoPri == 0){
			aux->priElem = (int *) malloc(sizeof(int));
			* ((int *)(aux->priElem)) = *((int*)pri);
		}
		else{
			aux->priElem = (char *) malloc((strlen((char*)pri)+1)*sizeof(char));
			strcpy(aux->priElem,pri);
		}
		aux-> segElem = seg;
		return aux;
	}

/***********************************************
destroiTuplo - Liberta a mem�ria ocupada pela inst�ncia da estrutura associada ao tuplo.
Par�metros:
	t - tuplo a destruir
Retorno:
Pr�-condi��es: t != NULL
***********************************************/
void destroiTuplo(tuplo t){
	free(t->priElem);
	free(t);
}

/***********************************************
priTuplo - Retorna o primeiro elemento no tuplo dado.
Par�metros:
	t - tuplo
Retorno: elemento (void *)
Pr�-condi��es: t != NULL
***********************************************/
void * priTuplo(tuplo t){
	return t->priElem;
}

/***********************************************
segTuplo - Retorna o segundo elemento no tuplo dado.
Par�metros:
	t - tuplo
Retorno: elemento (void *)
Pr�-condi��es: t != NULL
***********************************************/
void * segTuplo(tuplo t){
	return t->segElem;
}



